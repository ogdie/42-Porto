from mazegen_core.direction import Direction
from mazegen_core.maze import build_full_walls_maze


def make_maze(width=5, height=5):
    return build_full_walls_maze(
        width, height, entry=(0, 0), exit_coord=(width - 1, height - 1), blocked=set()
    )


def test_full_walls_all_closed():
    maze = make_maze()
    for row in maze.cells:
        for cell in row:
            assert cell.to_hex_digit() == "F"


def test_in_bounds():
    maze = make_maze(4, 3)
    assert maze.in_bounds((0, 0))
    assert maze.in_bounds((3, 2))
    assert not maze.in_bounds((4, 0))
    assert not maze.in_bounds((0, 3))
    assert not maze.in_bounds((-1, 0))


def test_open_between_is_symmetric():
    maze = make_maze(3, 3)
    maze.open_between((0, 0), (1, 0))
    assert not maze.cell_at((0, 0)).has_wall(Direction.EAST)
    assert not maze.cell_at((1, 0)).has_wall(Direction.WEST)
    # every other wall of both cells stays closed
    assert maze.cell_at((0, 0)).has_wall(Direction.SOUTH)
    assert maze.cell_at((1, 0)).has_wall(Direction.NORTH)


def test_direction_between():
    maze = make_maze(3, 3)
    assert maze.direction_between((1, 1), (1, 0)) is Direction.NORTH
    assert maze.direction_between((1, 1), (2, 1)) is Direction.EAST
