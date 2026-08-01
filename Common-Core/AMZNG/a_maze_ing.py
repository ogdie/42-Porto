#!/usr/bin/env python3
"""a_maze_ing.py: main entry point of the A-Maze-ing project.

Usage:
    python3 a_maze_ing.py config.txt

Reads a configuration file, generates a maze accordingly, writes it to
the configured output file using the hexadecimal wall format, and opens
a graphical window (MLX) showing the maze.
"""

from __future__ import annotations

import sys

from mazegen_core import (
    ConfigError,
    GenerationError,
    MazeConfig,
    MazeGenerator,
    load_config,
    write_maze,
)

from mlx_renderer import show_maze_window


def main(argv: list) -> int:

    if len(argv) != 2:
        program_name = argv[0] if len(argv) > 0 else "a_maze_ing.py"
        print(f"Usage: python3 {program_name} config.txt", file=sys.stderr)
        return 1

    config_path = argv[1]

    try:
        config = load_config(config_path)
    except ConfigError as error:
        print(f"Configuration error: {error}", file=sys.stderr)
        return 1

    try:
        maze, generator = _generate(config)
    except GenerationError as error:
        print(f"Maze generation error: {error}", file=sys.stderr)
        return 1

    try:
        write_maze(maze, config.output_file)
    except OSError as error:
        print(f"Could not write output file '{config.output_file}': {error}", file=sys.stderr)
        return 1

    for warning in generator.last_warnings:
        print(f"Warning: {warning}", file=sys.stderr)

    print(f"Maze written to '{config.output_file}'.")

    show_maze_window(maze, generator)

    return 0


def _generate(config: MazeConfig) -> tuple:

    generator = MazeGenerator(
        width=config.width,
        height=config.height,
        entry=config.entry,
        exit_coord=config.exit,
        perfect=config.perfect,
        seed=config.seed,
        draw_pattern=config.draw_pattern,
    )

    maze = generator.generate()

    return maze, generator


if __name__ == "__main__":
    sys.exit(main(sys.argv))
