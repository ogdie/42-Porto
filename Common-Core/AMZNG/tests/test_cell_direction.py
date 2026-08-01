from mazegen_core.cell import Cell
from mazegen_core.direction import ALL_DIRECTIONS, Direction


def test_direction_bits_match_subject_spec():
    assert Direction.NORTH.bit == 1
    assert Direction.EAST.bit == 2
    assert Direction.SOUTH.bit == 4
    assert Direction.WEST.bit == 8


def test_direction_opposites():
    assert Direction.NORTH.opposite is Direction.SOUTH
    assert Direction.EAST.opposite is Direction.WEST
    assert Direction.SOUTH.opposite is Direction.NORTH
    assert Direction.WEST.opposite is Direction.EAST


def test_cell_starts_fully_closed():
    cell = Cell()
    assert all(cell.has_wall(d) for d in ALL_DIRECTIONS)
    assert cell.to_hex_digit() == "F"


def test_cell_open_close_wall():
    cell = Cell()
    cell.open_wall(Direction.NORTH)
    cell.open_wall(Direction.WEST)
    assert not cell.has_wall(Direction.NORTH)
    assert not cell.has_wall(Direction.WEST)
    assert cell.has_wall(Direction.EAST)
    assert cell.has_wall(Direction.SOUTH)
    # walls open: N (1) and W (8) -> remaining closed: E (2) + S (4) = 6
    assert cell.to_hex_digit() == "6"
