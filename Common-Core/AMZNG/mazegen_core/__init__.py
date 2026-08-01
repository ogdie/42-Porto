"""mazegen_core: reusable maze generation library.

Public API:
    MazeGenerator - generates mazes (see generator.py)
    Maze, Cell, Direction, build_full_walls_maze - core data structures
    shortest_path - BFS solver

    Note: the graphical MLX display is intentionally NOT part of this
    module. See mlx_renderer.py at the project root.
"""

from __future__ import annotations

from mazegen_core.cell import Cell
from mazegen_core.config import ConfigError, MazeConfig, load_config
from mazegen_core.direction import ALL_DIRECTIONS, Direction
from mazegen_core.generator import GenerationError, MazeGenerator
from mazegen_core.maze import Maze, build_full_walls_maze
from mazegen_core.solver import shortest_path
from mazegen_core.validator import validate_maze
from mazegen_core.writer import write_maze

__all__ = [
    "Cell",
    "Direction",
    "ALL_DIRECTIONS",
    "Maze",
    "build_full_walls_maze",
    "MazeGenerator",
    "GenerationError",
    "shortest_path",
    "validate_maze",
    "write_maze",
    "load_config",
    "MazeConfig",
    "ConfigError",
]

__version__ = "1.0.0"
