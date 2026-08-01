"""Graphical maze display for a_maze_ing.py, using the 42 MiniLibX (MLX)
library.

This module opens a real window and draws the maze into an off-screen
image buffer (one pixel at a time, by writing raw bytes), then sends
that whole image to the window in a single call. This is done instead
of calling mlx_pixel_put directly on the window for every pixel,
because on some setups (WSLg included) mlx_pixel_put fails repeatedly
with "can't get next sw image" -- drawing to our own image buffer and
blitting it once avoids that code path entirely.

The 'mlx' package used here is not installed through pip (the wheel
file the school gives out is not named the standard way pip expects):
it is vendored directly inside this repository, in the mlx/ folder at
the project root.

This file is deliberately kept OUTSIDE the mazegen_core package: the
subject requires mazegen_core to be a standalone, pip-installable,
reusable module. If the graphical code lived inside mazegen_core, that
module would only work for people who also had this vendored mlx/
folder next to their code, which defeats the point of it being
reusable. mazegen_core knows nothing about MLX; this file is the only
place that does.
"""

from __future__ import annotations

import sys

from mazegen_core import Direction, GenerationError, Maze, MazeGenerator, shortest_path

from mlx import Mlx

# Tamanho de cada célula do labirinto, em pixels.
_CELL_SIZE = 24

# Espessura das paredes, em pixels.
_WALL_THICKNESS = 2

_COLOR_BACKGROUND = 0x000000
_COLOR_ENTRY = 0x00CC66
_COLOR_EXIT = 0xCC3333
_COLOR_PATH = 0xFFD700
_COLOR_PATTERN = 0x555555

# Lista de cores que a tecla 'c' vai percorrer, uma a cada aperto.
_WALL_COLORS = [
    0xFFFFFF,
    0xFF0000,
    0x00FF00,
    0xFFFF00,
    0x2288FF,
    0xFF00FF,
    0x00FFFF,
]

# Códigos de tecla X11 (Linux). Nas máquinas da 42 e no WSL com MLX
# instalado, teclas de letra minúscula usam o mesmo valor do código
# ASCII da letra. Se uma tecla não responder como esperado, o valor
# recebido é impresso no terminal (ver _on_key) para facilitar o ajuste.
_KEY_R = ord("r")
_KEY_P = ord("p")
_KEY_C = ord("c")
_KEY_Q = ord("q")
_KEY_ESC = 65307

# Código de evento X11 para "o utilizador fechou a janela" (botão X).
_EVENT_CLOSE_WINDOW = 33


class AppState:

    # Guarda tudo o que os "hooks" (funções chamadas pelo MLX quando
    # acontece um evento) precisam de saber: a ligação à biblioteca MLX,
    # a janela, a imagem onde desenhamos, o labirinto atual, o gerador,
    # e as opções de exibição.
    def __init__(
        self,
        mlx: Mlx,
        mlx_ptr: object,
        win_ptr: object,
        img_ptr: object,
        image_data: memoryview,
        bytes_per_pixel: int,
        bytes_per_row: int,
        width_px: int,
        height_px: int,
        maze: Maze,
        generator: MazeGenerator,
    ) -> None:

        self.mlx = mlx
        self.mlx_ptr = mlx_ptr
        self.win_ptr = win_ptr
        self.img_ptr = img_ptr
        self.image_data: memoryview = image_data
        self.bytes_per_pixel = bytes_per_pixel
        self.bytes_per_row = bytes_per_row
        self.width_px = width_px
        self.height_px = height_px
        self.maze = maze
        self.generator = generator
        self.show_path = False
        self.color_index = 0


# Abre a janela, cria a imagem onde vamos desenhar, desenha o labirinto,
# e entra no loop de eventos do MLX. Só volta a devolver o controlo
# quando o utilizador fecha a janela ou carrega em 'q' / Esc.
def show_maze_window(maze: Maze, generator: MazeGenerator) -> None:

    mlx = Mlx()
    mlx_ptr = mlx.mlx_init()

    width_px = maze.width * _CELL_SIZE + 1
    height_px = maze.height * _CELL_SIZE + 1

    win_ptr = mlx.mlx_new_window(mlx_ptr, width_px, height_px, "A-Maze-ing")
    img_ptr = mlx.mlx_new_image(mlx_ptr, width_px, height_px)

    image_data, bits_per_pixel, bytes_per_row, _pixel_format = mlx.mlx_get_data_addr(img_ptr)
    bytes_per_pixel = bits_per_pixel // 8

    state = AppState(
        mlx,
        mlx_ptr,
        win_ptr,
        img_ptr,
        image_data,
        bytes_per_pixel,
        bytes_per_row,
        width_px,
        height_px,
        maze,
        generator,
    )

    _draw_maze(state)

    mlx.mlx_key_hook(win_ptr, _on_key, state)
    mlx.mlx_hook(win_ptr, _EVENT_CLOSE_WINDOW, 0, _on_close, state)

    print("Janela aberta. Comandos: [r]egenerate  [p]ath toggle  [c]olour  [q]uit")

    mlx.mlx_loop(mlx_ptr)

    mlx.mlx_destroy_image(mlx_ptr, img_ptr)
    mlx.mlx_destroy_window(mlx_ptr, win_ptr)
    mlx.mlx_release(mlx_ptr)


# Chamada pelo MLX sempre que uma tecla é premida.
def _on_key(keynum: int, state: AppState) -> None:

    if keynum == _KEY_Q or keynum == _KEY_ESC:
        state.mlx.mlx_loop_exit(state.mlx_ptr)
        return

    elif keynum == _KEY_R:
        _regenerate(state)

    elif keynum == _KEY_P:
        state.show_path = not state.show_path

    elif keynum == _KEY_C:
        state.color_index = (state.color_index + 1) % len(_WALL_COLORS)

    else:
        print(f"Tecla desconhecida (código {keynum}).")
        return

    _draw_maze(state)


# Chamada pelo MLX quando o utilizador clica no X da janela.
def _on_close(state: AppState) -> None:
    state.mlx.mlx_loop_exit(state.mlx_ptr)


def _regenerate(state: AppState) -> None:

    state.generator.reseed(None)

    try:
        state.maze = state.generator.generate()
    except GenerationError as error:
        print(f"Could not regenerate maze: {error}", file=sys.stderr)
        return

    for warning in state.generator.last_warnings:
        print(f"Warning: {warning}", file=sys.stderr)


# Escreve uma cor (0xRRGGBB) num pixel do NOSSO buffer de imagem (não
# na janela diretamente). "color" é escrito byte a byte, do menos
# significativo (azul) para o mais significativo, que é a ordem que a
# MLX espera em Linux para imagens de 32 bits.
def _put_pixel(state: AppState, x: int, y: int, color: int) -> None:

    if x < 0 or x >= state.width_px or y < 0 or y >= state.height_px:
        return

    offset = y * state.bytes_per_row + x * state.bytes_per_pixel

    remaining_color = color
    byte_index = 0

    while byte_index < state.bytes_per_pixel:

        if byte_index == 3:
            # 4o byte, quando existe, costuma ser o canal alfa
            # (transparencia). Alguns ambientes (ex: WSLg) tratam alfa 0
            # como "totalmente transparente" e nao desenham nada. Forcamos
            # sempre opaco.
            state.image_data[offset + byte_index] = 0xFF
        else:
            state.image_data[offset + byte_index] = remaining_color & 0xFF
            remaining_color = remaining_color >> 8

        byte_index = byte_index + 1


# Limpa a imagem inteira com a cor de fundo.
def _clear_image(state: AppState, width_px: int, height_px: int) -> None:

    y = 0
    while y < height_px:

        x = 0
        while x < width_px:
            _put_pixel(state, x, y, _COLOR_BACKGROUND)
            x = x + 1

        y = y + 1


# Desenha o labirinto todo no buffer de imagem: fundo, paredes, entrada,
# saída, padrão "42", e o caminho mais curto (se ativado). No final,
# manda a imagem inteira para a janela de uma só vez.
def _draw_maze(state: AppState) -> None:

    maze = state.maze

    width_px = maze.width * _CELL_SIZE + 1
    height_px = maze.height * _CELL_SIZE + 1

    _clear_image(state, width_px, height_px)

    wall_color = _WALL_COLORS[state.color_index]

    if state.show_path:
        path_cells = _path_cells(maze)
    else:
        path_cells = set()

    for y in range(maze.height):
        for x in range(maze.width):

            coord = (x, y)

            if maze.is_blocked(coord):
                _fill_cell(state, coord, _COLOR_PATTERN, 1.0)
            elif coord == maze.entry:
                _fill_cell(state, coord, _COLOR_ENTRY, 0.5)
            elif coord == maze.exit:
                _fill_cell(state, coord, _COLOR_EXIT, 0.5)
            elif coord in path_cells:
                _fill_cell(state, coord, _COLOR_PATH, 0.4)

            _draw_cell_walls(state, coord, wall_color)

    state.mlx.mlx_put_image_to_window(state.mlx_ptr, state.win_ptr, state.img_ptr, 0, 0)


# Percorre o caminho mais curto letra a letra, e devolve o conjunto de
# coordenadas por onde ele passa.
def _path_cells(maze: Maze) -> set:

    cells = set()
    cells.add(maze.entry)

    current = maze.entry
    path = shortest_path(maze)

    for letter in path:
        direction = _direction_from_letter(letter)
        current = maze.neighbor(current, direction)
        cells.add(current)

    return cells


def _direction_from_letter(letter: str) -> Direction:

    for direction in Direction:
        if direction.letter == letter:
            return direction

    raise ValueError(f"Unknown direction letter: {letter}")


# Desenha as 4 paredes de uma célula (só as que estiverem fechadas).
def _draw_cell_walls(state: AppState, coord: tuple, color: int) -> None:

    x = coord[0]
    y = coord[1]

    left = x * _CELL_SIZE
    top = y * _CELL_SIZE
    right = left + _CELL_SIZE
    bottom = top + _CELL_SIZE

    cell = state.maze.cell_at(coord)

    if cell.has_wall(Direction.NORTH):
        _draw_horizontal_line(state, left, right, top, color)

    if cell.has_wall(Direction.SOUTH):
        _draw_horizontal_line(state, left, right, bottom, color)

    if cell.has_wall(Direction.WEST):
        _draw_vertical_line(state, top, bottom, left, color)

    if cell.has_wall(Direction.EAST):
        _draw_vertical_line(state, top, bottom, right, color)


def _draw_horizontal_line(state: AppState, x_start: int, x_end: int, y: int, color: int) -> None:

    thickness = 0
    while thickness < _WALL_THICKNESS:

        x = x_start
        while x <= x_end:
            _put_pixel(state, x, y + thickness, color)
            x = x + 1

        thickness = thickness + 1


def _draw_vertical_line(state: AppState, y_start: int, y_end: int, x: int, color: int) -> None:

    thickness = 0
    while thickness < _WALL_THICKNESS:

        y = y_start
        while y <= y_end:
            _put_pixel(state, x + thickness, y, color)
            y = y + 1

        thickness = thickness + 1


# Pinta um marcador quadrado, centrado na célula, com um tamanho
# proporcional a "ratio" (1.0 preenche a célula toda, 0.5 preenche
# metade, etc).
def _fill_cell(state: AppState, coord: tuple, color: int, ratio: float) -> None:

    x = coord[0]
    y = coord[1]

    size = int(_CELL_SIZE * ratio)
    margin = (_CELL_SIZE - size) // 2

    left = x * _CELL_SIZE + margin
    top = y * _CELL_SIZE + margin

    row = 0
    while row < size:

        col = 0
        while col < size:
            _put_pixel(state, left + col, top + row, color)
            col = col + 1

        row = row + 1
