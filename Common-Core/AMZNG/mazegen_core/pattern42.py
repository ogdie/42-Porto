from __future__ import annotations

# Bitmap 5 (altura) x 3 (largura) por dígito, no estilo de um mostrador
# de 7 segmentos "em blocos". "1" = célula totalmente fechada (faz parte
# do desenho), "0" = célula normal do labirinto.
_DIGIT_4 = [
    "101",
    "101",
    "111",
    "001",
    "001",
]

_DIGIT_2 = [
    "111",
    "001",
    "111",
    "100",
    "111",
]

_DIGIT_HEIGHT = 5
_DIGIT_WIDTH = 3
_GAP = 1
_PATTERN_WIDTH = _DIGIT_WIDTH * 2 + _GAP
_PATTERN_HEIGHT = _DIGIT_HEIGHT

# Margem mínima de células "normais" que deve sobrar ao redor do padrão,
# para não colar o "42" nas bordas do labirinto.
_MARGIN = 1


class PatternTooLargeError(Exception):
    """Raised when the maze is too small to fit the '42' pattern."""


# Calcula as coordenadas bloqueadas para desenhar "42", centrado no
# labirinto, evitando as células de entrada e saída sempre que possível.
def build_42_pattern(width: int, height: int, entry: tuple, exit_coord: tuple) -> set:

    required_width = _PATTERN_WIDTH + _MARGIN * 2
    required_height = _PATTERN_HEIGHT + _MARGIN * 2

    if width < required_width or height < required_height:
        raise PatternTooLargeError(
            "Maze is too small to fit the '42' pattern "
            f"(needs at least {required_width}x{required_height})."
        )

    offset_x = (width - _PATTERN_WIDTH) // 2
    offset_y = (height - _PATTERN_HEIGHT) // 2

    blocked = set()

    digits = [(_DIGIT_4, 0), (_DIGIT_2, _DIGIT_WIDTH + _GAP)]

    for digit_bitmap, digit_offset in digits:

        row_index = 0

        for row in digit_bitmap:

            col_index = 0

            for char in row:

                if char == "1":
                    x = offset_x + digit_offset + col_index
                    y = offset_y + row_index
                    blocked.add((x, y))

                col_index = col_index + 1

            row_index = row_index + 1

    if entry in blocked or exit_coord in blocked:
        raise PatternTooLargeError(
            "The '42' pattern would overlap the entry or exit cell."
        )

    return blocked
