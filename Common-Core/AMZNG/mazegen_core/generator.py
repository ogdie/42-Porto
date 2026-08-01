"""Reusable, standalone maze generator.

Basic usage:

    from mazegen_core import MazeGenerator

    generator = MazeGenerator(
        width=20,
        height=15,
        entry=(0, 0),
        exit_coord=(19, 14),
        perfect=True,
        seed=42,
    )
    maze = generator.generate()

    from mazegen_core import shortest_path
    print(shortest_path(maze))   # e.g. "EESSN..."
    cell = maze.cell_at((0, 0))  # access the generated structure

Passing the same seed always produces the same maze, which makes
generation reproducible.
"""

from __future__ import annotations

import random

from mazegen_core.direction import EAST_SOUTH
from mazegen_core.maze import Maze, build_full_walls_maze
from mazegen_core.pattern42 import PatternTooLargeError, build_42_pattern
from mazegen_core.validator import open_area_violations, validate_maze

_DEFAULT_EXTRA_PASSAGE_RATIO = 0.12


class GenerationError(Exception):
    """Raised when a maze cannot be generated with the given parameters."""


class MazeGenerator:

    def __init__(
        self,
        width: int,
        height: int,
        entry: tuple,
        exit_coord: tuple,
        perfect: bool = True,
        seed: int | None = None,
        draw_pattern: bool = True,
        extra_passage_ratio: float = _DEFAULT_EXTRA_PASSAGE_RATIO,
    ) -> None:

        self.width = width
        self.height = height
        self.entry = entry
        self.exit_coord = exit_coord
        self.perfect = perfect
        self.seed = seed
        self.draw_pattern = draw_pattern
        self.extra_passage_ratio = extra_passage_ratio
        self.rng = random.Random(seed)
        self.last_warnings: list = []

    # Redefine a semente aleatória do generator (útil para "regenerar" um
    # novo labirinto sem criar uma nova instância).
    def reseed(self, seed: int | None = None) -> None:
        self.seed = seed
        self.rng = random.Random(seed)

    # Gera e devolve um novo Maze válido de acordo com os parâmetros do generator.
    def generate(self) -> Maze:

        self.last_warnings = []
        self._validate_parameters()

        blocked = self._build_pattern()

        maze = build_full_walls_maze(
            width=self.width,
            height=self.height,
            entry=self.entry,
            exit_coord=self.exit_coord,
            blocked=blocked,
        )

        visited = self._carve_spanning_tree(maze)

        expected = self.width * self.height - len(blocked)

        if len(visited) != expected:
            raise GenerationError(
                "Failed to generate a fully connected maze "
                f"({len(visited)}/{expected} cells reachable). "
                "Try different ENTRY/EXIT coordinates or a smaller maze."
            )

        if not self.perfect:
            self._add_loops(maze, visited)

        errors = validate_maze(maze, perfect_required=self.perfect)

        if len(errors) > 0:
            raise GenerationError(
                "Generated maze failed internal validation: " + "; ".join(errors)
            )

        return maze

    def _validate_parameters(self) -> None:

        if self.width <= 0 or self.height <= 0:
            raise GenerationError("WIDTH and HEIGHT must be positive integers.")

        entry_x = self.entry[0]
        entry_y = self.entry[1]

        if entry_x < 0 or entry_x >= self.width or entry_y < 0 or entry_y >= self.height:
            raise GenerationError(f"ENTRY {self.entry} is outside the maze bounds.")

        exit_x = self.exit_coord[0]
        exit_y = self.exit_coord[1]

        if exit_x < 0 or exit_x >= self.width or exit_y < 0 or exit_y >= self.height:
            raise GenerationError(f"EXIT {self.exit_coord} is outside the maze bounds.")

        if self.entry == self.exit_coord:
            raise GenerationError("ENTRY and EXIT must be different cells.")

    def _build_pattern(self) -> set:

        if not self.draw_pattern:
            return set()

        try:
            blocked = build_42_pattern(self.width, self.height, self.entry, self.exit_coord)
            return blocked
        except PatternTooLargeError as error:
            self.last_warnings.append(f"'42' pattern skipped: {error}")
            return set()

    # Algoritmo "recursive backtracker" (DFS aleatorizado, em pilha para
    # evitar limites de recursão do Python), que gera uma árvore geradora
    # -- ou seja, um labirinto perfeito -- cobrindo todas as células não
    # bloqueadas pelo padrão "42".
    def _carve_spanning_tree(self, maze: Maze) -> set:

        start = maze.entry

        visited = set()
        visited.add(start)

        stack = [start]

        while len(stack) > 0:

            current = stack[-1]
            neighbors = maze.walkable_neighbors(current)

            unvisited = []

            for direction, next_coord in neighbors:
                if next_coord not in visited:
                    unvisited.append(next_coord)

            if len(unvisited) == 0:
                stack.pop()
                continue

            next_coord = self.rng.choice(unvisited)
            maze.open_between(current, next_coord)
            visited.add(next_coord)
            stack.append(next_coord)

        return visited

    # Adiciona ligações extra (loops) quando o labirinto não precisa de
    # ser perfeito, sempre respeitando o limite de largura de corredor.
    def _add_loops(self, maze: Maze, visited: set) -> None:

        candidates = []

        for coord in visited:
            for direction in EAST_SOUTH:

                neighbor = maze.neighbor(coord, direction)

                if neighbor not in visited:
                    continue

                if maze.cell_at(coord).has_wall(direction):
                    candidates.append((coord, neighbor))

        self.rng.shuffle(candidates)

        target = int(len(candidates) * self.extra_passage_ratio)
        if target < 1:
            target = 1

        added = 0

        for first, second in candidates:

            if added >= target:
                break

            maze.open_between(first, second)

            if len(open_area_violations(maze)) > 0:
                direction = maze.direction_between(first, second)
                maze.cell_at(first).close_wall(direction)
                maze.cell_at(second).close_wall(direction.opposite)
                continue

            added = added + 1

        if added == 0:
            self.last_warnings.append(
                "Could not add extra loops without violating the corridor-width "
                "rule; the maze may still be perfect."
            )
