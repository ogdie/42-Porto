import pytest

from mazegen_core.config import ConfigError, load_config
from mazegen_core.generator import MazeGenerator
from mazegen_core.solver import shortest_path
from mazegen_core.writer import write_maze


def test_shortest_path_matches_direction_letters():
    generator = MazeGenerator(
        width=15, height=10, entry=(0, 0), exit_coord=(14, 9), perfect=True, seed=3
    )
    maze = generator.generate()
    path = shortest_path(maze)
    assert set(path) <= {"N", "E", "S", "W"}

    # walking the path from entry must land exactly on exit
    x, y = maze.entry
    deltas = {"N": (0, -1), "E": (1, 0), "S": (0, 1), "W": (-1, 0)}
    for letter in path:
        dx, dy = deltas[letter]
        x, y = x + dx, y + dy
    assert (x, y) == maze.exit


def test_shortest_path_entry_equals_exit_is_empty():
    generator = MazeGenerator(
        width=10, height=10, entry=(0, 0), exit_coord=(9, 9), perfect=True, seed=1
    )
    maze = generator.generate()
    maze.exit = maze.entry
    assert shortest_path(maze) == ""


def test_write_maze_format(tmp_path):
    generator = MazeGenerator(
        width=8, height=6, entry=(0, 0), exit_coord=(7, 5), perfect=True, seed=2
    )
    maze = generator.generate()
    output_file = tmp_path / "maze.txt"
    write_maze(maze, str(output_file))

    lines = output_file.read_text(encoding="utf-8").split("\n")
    grid_lines = lines[:6]
    assert all(len(line) == 8 for line in grid_lines)
    assert all(c in "0123456789ABCDEF" for line in grid_lines for c in line)
    assert lines[6] == ""
    assert lines[7] == "0,0"
    assert lines[8] == "7,5"
    assert set(lines[9]) <= {"N", "E", "S", "W"}


def test_config_missing_file():
    with pytest.raises(ConfigError):
        load_config("/nonexistent/path/config.txt")


def test_config_missing_required_key(tmp_path):
    config_file = tmp_path / "config.txt"
    config_file.write_text("WIDTH=10\nHEIGHT=10\n")
    with pytest.raises(ConfigError):
        load_config(str(config_file))


def test_config_bad_syntax(tmp_path):
    config_file = tmp_path / "config.txt"
    config_file.write_text("not a key value line\n")
    with pytest.raises(ConfigError):
        load_config(str(config_file))


def test_config_valid(tmp_path):
    config_file = tmp_path / "config.txt"
    config_file.write_text(
        "WIDTH=10\nHEIGHT=10\nENTRY=0,0\nEXIT=9,9\nOUTPUT_FILE=out.txt\nPERFECT=True\nSEED=1\n"
    )
    config = load_config(str(config_file))
    assert config.width == 10
    assert config.entry == (0, 0)
    assert config.exit == (9, 9)
    assert config.perfect is True
    assert config.seed == 1
