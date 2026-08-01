from __future__ import annotations

from mazegen_core.direction import ALL_DIRECTIONS, Direction
from mazegen_core.maze import Maze

# Tamanho da janela usada para detetar áreas abertas grandes demais.
# O subject proíbe corredores com mais de 2 células de largura, ou seja,
# nenhuma janela 3x3 de células pode estar totalmente aberta entre si.
_OPEN_AREA_WINDOW = 3


# Valida um labirinto por completo, devolvendo a lista de problemas
# encontrados (lista vazia significa que o labirinto é válido).
def validate_maze(maze: Maze, perfect_required: bool) -> list:

    errors = []

    for error in _validate_entry_exit(maze):
        errors.append(error)

    for error in _validate_borders(maze):
        errors.append(error)

    reachable = _reachable_cells(maze)

    for error in _validate_connectivity(maze, reachable):
        errors.append(error)

    for error in open_area_violations(maze):
        errors.append(error)

    if perfect_required:
        for error in _validate_perfect(maze, reachable):
            errors.append(error)

    return errors


def _validate_entry_exit(maze: Maze) -> list:

    errors = []

    if not maze.in_bounds(maze.entry):
        errors.append(f"Entry {maze.entry} is out of maze bounds.")

    if not maze.in_bounds(maze.exit):
        errors.append(f"Exit {maze.exit} is out of maze bounds.")

    if maze.entry == maze.exit:
        errors.append("Entry and exit must be different cells.")

    if maze.is_blocked(maze.entry):
        errors.append("Entry cell overlaps the '42' pattern.")

    if maze.is_blocked(maze.exit):
        errors.append("Exit cell overlaps the '42' pattern.")

    return errors


# Confirma que não existem paredes abertas a apontar para fora do labirinto.
def _validate_borders(maze: Maze) -> list:

    errors = []

    for y in range(maze.height):
        for x in range(maze.width):

            coord = (x, y)
            cell = maze.cell_at(coord)

            for direction in ALL_DIRECTIONS:

                neighbor = maze.neighbor(coord, direction)

                if maze.in_bounds(neighbor):
                    continue

                if not cell.has_wall(direction):
                    errors.append(
                        f"Cell {coord} has an open wall ({direction.letter}) "
                        "pointing outside the maze bounds."
                    )

    return errors


# Faz uma busca em largura a partir da entrada, para descobrir todas as
# células que conseguimos alcançar.
def _reachable_cells(maze: Maze) -> set:

    if maze.is_blocked(maze.entry) or not maze.in_bounds(maze.entry):
        return set()

    visited = set()
    visited.add(maze.entry)

    queue = [maze.entry]

    while len(queue) > 0:

        current = queue.pop(0)
        cell = maze.cell_at(current)

        for direction in ALL_DIRECTIONS:

            if cell.has_wall(direction):
                continue

            next_coord = maze.neighbor(current, direction)

            if next_coord in visited:
                continue

            if not maze.in_bounds(next_coord):
                continue

            visited.add(next_coord)
            queue.append(next_coord)

    return visited


def _validate_connectivity(maze: Maze, reachable: set) -> list:

    errors = []
    total_cells = maze.width * maze.height

    for y in range(maze.height):
        for x in range(maze.width):

            coord = (x, y)

            if maze.is_blocked(coord):
                continue

            if coord not in reachable:
                errors.append(f"Cell {coord} is isolated from the rest of the maze.")

    expected_reachable = total_cells - len(maze.blocked)

    if len(reachable) != expected_reachable:
        errors.append(
            "Maze is not fully connected: "
            f"{len(reachable)}/{expected_reachable} reachable cells."
        )

    return errors


def open_area_violations(maze: Maze) -> list:

    errors: list[str] = []

    if maze.width < _OPEN_AREA_WINDOW or maze.height < _OPEN_AREA_WINDOW:
        return errors

    for top in range(maze.height - _OPEN_AREA_WINDOW + 1):
        for left in range(maze.width - _OPEN_AREA_WINDOW + 1):

            if _window_fully_open(maze, left, top):
                errors.append(
                    f"Open area of {_OPEN_AREA_WINDOW}x{_OPEN_AREA_WINDOW} cells "
                    f"detected at ({left}, {top}); corridors cannot be wider than 2 cells."
                )

    return errors


# Verifica se todas as paredes internas de uma janela NxN estão abertas,
# o que significaria uma sala totalmente aberta (proibido para N=3).
def _window_fully_open(maze: Maze, left: int, top: int) -> bool:

    size = _OPEN_AREA_WINDOW

    for y in range(top, top + size):
        for x in range(left, left + size - 1):

            if maze.is_blocked((x, y)) or maze.is_blocked((x + 1, y)):
                return False

            if maze.cell_at((x, y)).has_wall(Direction.EAST):
                return False

    for x in range(left, left + size):
        for y in range(top, top + size - 1):

            if maze.is_blocked((x, y)) or maze.is_blocked((x, y + 1)):
                return False

            if maze.cell_at((x, y)).has_wall(Direction.SOUTH):
                return False

    return True


def _validate_perfect(maze: Maze, reachable: set) -> list:

    errors = []

    open_wall_count = 0

    for coord in reachable:

        cell = maze.cell_at(coord)

        for direction in ALL_DIRECTIONS:
            if not cell.has_wall(direction):
                open_wall_count = open_wall_count + 1

    edges = open_wall_count // 2
    nodes = len(reachable)

    if edges != nodes - 1:

        if edges > nodes - 1:
            errors.append(
                f"Maze is not perfect: found a loop "
                f"({edges} passages for {nodes} cells, expected {nodes - 1})."
            )
        else:
            errors.append(
                f"Maze is not perfect: disconnected regions "
                f"({edges} passages for {nodes} cells, expected {nodes - 1})."
            )

    return errors
