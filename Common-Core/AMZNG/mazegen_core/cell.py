from __future__ import annotations

from mazegen_core.direction import ALL_DIRECTIONS, Direction


class Cell:

    # Uma célula guarda o conjunto de paredes fechadas.
    # No início, todas as 4 paredes estão fechadas.
    def __init__(self) -> None:

        walls = set()

        for direction in ALL_DIRECTIONS:
            walls.add(direction)

        self.walls = walls

    # Abre a parede numa direção (tira essa direção do conjunto).
    def open_wall(self, direction: Direction) -> None:
        self.walls.discard(direction)

    # Fecha a parede numa direção (põe essa direção no conjunto).
    def close_wall(self, direction: Direction) -> None:
        self.walls.add(direction)

    # Verifica se a parede numa direção está fechada.
    def has_wall(self, direction: Direction) -> bool:
        if direction in self.walls:
            return True
        return False

    # Converte as paredes fechadas num único dígito hexadecimal,
    # somando o valor (bit) de cada direção fechada.
    def to_hex_digit(self) -> str:

        value = 0

        for direction in self.walls:
            value = value | direction.bit

        return f"{value:X}"
