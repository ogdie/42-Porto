from __future__ import annotations

from mazegen_core.cell import Cell
from mazegen_core.direction import ALL_DIRECTIONS, Direction
from mazegen_core.types import Coordinate


class Maze:

    # Um labirinto guarda a largura, a altura, a entrada, a saída,
    # a grelha de células, e o conjunto de células bloqueadas (que
    # fazem parte do desenho "42" e não entram no labirinto navegável).
    def __init__(
        self,
        width: int,
        height: int,
        entry: Coordinate,
        exit: Coordinate,
        cells: list[list[Cell]],
        blocked: set,
    ) -> None:

        self.width = width
        self.height = height
        self.entry = entry
        self.exit = exit
        self.cells = cells
        self.blocked = blocked

    # Verifica se uma coordenada está dentro dos limites do labirinto.
    def in_bounds(self, coord: Coordinate) -> bool:

        x = coord[0]
        y = coord[1]

        if x < 0:
            return False

        if x >= self.width:
            return False

        if y < 0:
            return False

        if y >= self.height:
            return False

        return True

    # Verifica se uma coordenada faz parte do padrão "42" (bloqueada).
    def is_blocked(self, coord: Coordinate) -> bool:

        if coord in self.blocked:
            return True

        return False

    # Devolve a célula existente na coordenada indicada.
    def cell_at(self, coord: Coordinate) -> Cell:

        x = coord[0]
        y = coord[1]

        cell = self.cells[y][x]

        return cell

    # Calcula a coordenada da célula vizinha numa determinada direção.
    def neighbor(self, coord: Coordinate, direction: Direction) -> Coordinate:

        x = coord[0]
        y = coord[1]

        new_x = x + direction.dx
        new_y = y + direction.dy

        return (new_x, new_y)

    # Devolve todos os vizinhos válidos (dentro dos limites do labirinto).
    def valid_neighbors(self, coord: Coordinate) -> list:

        neighbors = []

        for direction in ALL_DIRECTIONS:

            next_coord = self.neighbor(coord, direction)

            if self.in_bounds(next_coord):
                neighbors.append((direction, next_coord))

        return neighbors

    # Devolve apenas os vizinhos válidos que não estão bloqueados
    # pelo padrão "42".
    def walkable_neighbors(self, coord: Coordinate) -> list:

        result = []

        for direction, next_coord in self.valid_neighbors(coord):

            if not self.is_blocked(next_coord):
                result.append((direction, next_coord))

        return result

    # Abre a parede entre duas células vizinhas (dos dois lados).
    def open_between(self, first: Coordinate, second: Coordinate) -> None:

        direction = self.direction_between(first, second)

        first_cell = self.cell_at(first)
        second_cell = self.cell_at(second)

        first_cell.open_wall(direction)
        second_cell.open_wall(direction.opposite)

    # Descobre a direção da segunda célula em relação à primeira.
    def direction_between(self, first: Coordinate, second: Coordinate) -> Direction:

        first_x = first[0]
        first_y = first[1]

        second_x = second[0]
        second_y = second[1]

        dx = second_x - first_x
        dy = second_y - first_y

        for direction in ALL_DIRECTIONS:

            if direction.dx == dx and direction.dy == dy:
                return direction

        raise ValueError(f"Cells are not direct neighbors: {first} -> {second}")

    # Devolve apenas os vizinhos que podem ser alcançados (sem parede).
    def open_neighbors(self, coord: Coordinate) -> list:

        result = []

        cell = self.cell_at(coord)

        neighbors = self.valid_neighbors(coord)

        for direction, next_coord in neighbors:

            if not cell.has_wall(direction):
                result.append((direction, next_coord))

        return result


# Cria um novo labirinto com todas as paredes fechadas.
# As células bloqueadas (padrão "42") também começam totalmente fechadas.
def build_full_walls_maze(
    width: int,
    height: int,
    entry: Coordinate,
    exit_coord: Coordinate,
    blocked: set,
) -> Maze:

    cells = []

    for y in range(height):

        row = []

        for x in range(width):
            cell = Cell()
            row.append(cell)

        cells.append(row)

    maze = Maze(
        width=width,
        height=height,
        entry=entry,
        exit=exit_coord,
        cells=cells,
        blocked=blocked,
    )

    return maze
