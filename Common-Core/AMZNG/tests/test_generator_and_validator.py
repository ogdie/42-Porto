import pytest

from mazegen_core.direction import ALL_DIRECTIONS
from mazegen_core.generator import GenerationError, MazeGenerator
from mazegen_core.validator import validate_maze


SIZES_AND_SEEDS = [
    (10, 10, 1),
    (20, 15, 42),
    (30, 8, 7),
    (9, 9, 0),
    (25, 25, 123),
]


@pytest.mark.parametrize("width,height,seed", SIZES_AND_SEEDS)
def test_perfect_maze_is_valid_and_connected(width, height, seed):
    generator = MazeGenerator(
        width=width,
        height=height,
        entry=(0, 0),
        exit_coord=(width - 1, height - 1),
        perfect=True,
        seed=seed,
    )
    maze = generator.generate()
    errors = validate_maze(maze, perfect_required=True)
    assert errors == []


@pytest.mark.parametrize("width,height,seed", SIZES_AND_SEEDS)
def test_non_perfect_maze_is_valid_and_connected(width, height, seed):
    generator = MazeGenerator(
        width=width,
        height=height,
        entry=(0, 0),
        exit_coord=(width - 1, height - 1),
        perfect=False,
        seed=seed,
    )
    maze = generator.generate()
    errors = validate_maze(maze, perfect_required=False)
    assert errors == []


def test_same_seed_is_reproducible():
    kwargs = dict(width=20, height=15, entry=(0, 0), exit_coord=(19, 14), perfect=True, seed=99)
    maze_a = MazeGenerator(**kwargs).generate()
    maze_b = MazeGenerator(**kwargs).generate()

    rows_a = ["".join(maze_a.cell_at((x, y)).to_hex_digit() for x in range(20)) for y in range(15)]
    rows_b = ["".join(maze_b.cell_at((x, y)).to_hex_digit() for x in range(20)) for y in range(15)]
    assert rows_a == rows_b


def test_different_seeds_usually_differ():
    kwargs = dict(width=20, height=15, entry=(0, 0), exit_coord=(19, 14), perfect=True)
    maze_a = MazeGenerator(seed=1, **kwargs).generate()
    maze_b = MazeGenerator(seed=2, **kwargs).generate()

    rows_a = ["".join(maze_a.cell_at((x, y)).to_hex_digit() for x in range(20)) for y in range(15)]
    rows_b = ["".join(maze_b.cell_at((x, y)).to_hex_digit() for x in range(20)) for y in range(15)]
    assert rows_a != rows_b


def test_invalid_parameters_raise_generation_error():
    with pytest.raises(GenerationError):
        MazeGenerator(width=0, height=5, entry=(0, 0), exit_coord=(0, 4)).generate()

    with pytest.raises(GenerationError):
        MazeGenerator(width=5, height=5, entry=(0, 0), exit_coord=(10, 10)).generate()

    with pytest.raises(GenerationError):
        MazeGenerator(width=5, height=5, entry=(0, 0), exit_coord=(0, 0)).generate()


def test_pattern_skipped_on_small_maze():
    generator = MazeGenerator(
        width=5, height=5, entry=(0, 0), exit_coord=(4, 4), perfect=True, seed=1
    )
    maze = generator.generate()
    assert maze.blocked == set()
    assert generator.last_warnings  # warning recorded


def test_perfect_maze_has_no_loops():
    generator = MazeGenerator(
        width=12, height=12, entry=(0, 0), exit_coord=(11, 11), perfect=True, seed=5
    )
    maze = generator.generate()
    nodes = 12 * 12 - len(maze.blocked)
    open_walls = sum(
        1
        for y in range(12)
        for x in range(12)
        for d in ALL_DIRECTIONS
        if not maze.cell_at((x, y)).has_wall(d)
    )
    assert open_walls // 2 == nodes - 1
