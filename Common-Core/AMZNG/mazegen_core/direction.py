from __future__ import annotations

from enum import Enum


class Direction(Enum):

    NORTH = ("N", 0, -1, 1)
    EAST = ("E", 1, 0, 2)
    SOUTH = ("S", 0, 1, 4)
    WEST = ("W", -1, 0, 8)

    def __init__(self, letter: str, dx: int, dy: int, bit: int) -> None:
        self.letter = letter
        self.dx = dx
        self.dy = dy
        self.bit = bit

    @property
    def opposite(self) -> Direction:
        opposites = {
            Direction.NORTH: Direction.SOUTH,
            Direction.EAST: Direction.WEST,
            Direction.SOUTH: Direction.NORTH,
            Direction.WEST: Direction.EAST,
        }
        return opposites[self]


ALL_DIRECTIONS = (
    Direction.NORTH,
    Direction.EAST,
    Direction.SOUTH,
    Direction.WEST,
)

# Usadas para percorrer cada par de células vizinhas uma única vez
# (evita processar a mesma parede duas vezes, uma a partir de cada lado).
EAST_SOUTH = (
    Direction.EAST,
    Direction.SOUTH,
)
