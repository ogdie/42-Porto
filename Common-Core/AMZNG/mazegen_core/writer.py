from __future__ import annotations

from mazegen_core.maze import Maze
from mazegen_core.solver import shortest_path


# Escreve o labirinto no formato de output definido pelo subject:
#   - uma linha por fila, um dígito hexadecimal por célula
#   - uma linha vazia
#   - coordenadas de entrada, coordenadas de saída, caminho mais curto (N/E/S/W)
# Todas as linhas terminam em '\n'.
def write_maze(maze: Maze, output_path: str) -> None:

    lines = []

    for y in range(maze.height):

        row = ""

        for x in range(maze.width):
            cell = maze.cell_at((x, y))
            row = row + cell.to_hex_digit()

        lines.append(row)

    lines.append("")
    lines.append(f"{maze.entry[0]},{maze.entry[1]}")
    lines.append(f"{maze.exit[0]},{maze.exit[1]}")
    lines.append(shortest_path(maze))

    content = "\n".join(lines) + "\n"

    output_file = open(output_path, "w", encoding="utf-8")
    output_file.write(content)
    output_file.close()
