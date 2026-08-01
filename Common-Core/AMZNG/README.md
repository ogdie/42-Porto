*This project has been created as part of the 42 curriculum by diemonte, jfaria-c.*

# A-Maze-ing

## Description

A-Maze-ing is a Python maze generator and solver. Given a configuration
file (dimensions, entry/exit points, and whether the maze should be
"perfect"), the program generates a valid, randomly-seeded maze, writes it
to a file using a compact hexadecimal wall encoding, and opens a
graphical window (MLX) showing the maze.

The maze generation logic is also packaged as a standalone, reusable,
pip-installable library (`mazegen_core` / `mazegen`), so it can be reused
in future projects without depending on this repository or on MLX.

## Instructions

### Requirements

- Python 3.10+
- No third-party runtime dependencies for the maze generator itself
  (standard library only).
- For the graphical display: the `mlx` package, vendored in this
  repository under `mlx/` (see "About the MLX library" below).

### Run the maze generator

```bash
python3 a_maze_ing.py config.txt
```

- `a_maze_ing.py` is the main program; the name is fixed by the subject.
- `config.txt` is the only argument: a plain text configuration file. A
  default one is provided at the root of this repository.

This opens a window showing the maze. Commands (keyboard, while the
window is focused):

| Key | Action |
|---|---|
| `r` | Regenerate a new maze (new random seed) and redraw it |
| `p` | Show / hide the shortest valid path from entry to exit |
| `c` | Cycle to the next wall colour |
| `q` / `Esc` | Quit (closing the window also works) |

### About the MLX library

The Python `mlx` package provided by 42 (`mlx-2.2-py3-ubuntu-any.whl` /
`mlx-2.2-py3-fedora-any.whl`) is **not** installed via `pip install`: its
filename does not follow the standard wheel naming convention, so pip
refuses it outright ("not a supported wheel on this platform"). Since it
is a plain `ctypes` wrapper around a bundled `libmlx.so` (no compilation
needed), it is vendored directly in this repository instead, under the
`mlx/` folder at the project root — `a_maze_ing.py` imports it from
there directly (`from mlx import Mlx`).

`libmlx.so` needs a couple of system libraries at runtime. On Ubuntu /
WSL:

```bash
sudo apt-get install -y libxcb-keysyms1 libvulkan1
```

It also needs a real X11 display to open a window: on Windows 11, WSL's
built-in WSLg provides this automatically; on the school's machines this
is already set up. If a key doesn't seem to do anything, the window
prints the raw key code it received to the terminal — check
`mlx_renderer.py` (`_KEY_R`, `_KEY_P`, etc.) if the codes need adjusting
for a different setup.

### Validate the output file

A validation script provided by 42 is included at `tools/output_validator.py`.
It checks that neighbouring cells agree on shared walls:

```bash
python3 tools/output_validator.py maze.txt
```

No output means no errors found.

### Run the tests (not graded, for development only)

```bash
pip install pytest --break-system-packages   # or use a virtualenv
python3 -m pytest tests/
```

### Lint

```bash
flake8 .
mypy . --warn-return-any --warn-unused-ignores --ignore-missing-imports --disallow-untyped-defs --check-untyped-defs
```

Both are configured via `setup.cfg` (line length 100, and the vendored
`mlx/` folder excluded, since it is 42's code, not ours).

### Build the reusable package

The `mazegen-1.0.0-py3-none-any.whl` file at the root of this repository
is a pre-built package, but it can be rebuilt from source at any time:

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install build
python3 -m build --wheel
pip install dist/mazegen-1.0.0-py3-none-any.whl
```

This package only contains `mazegen_core` (the maze generation logic).
It has no dependency on MLX or on the vendored `mlx/` folder — the
graphical display (`mlx_renderer.py`) is deliberately kept outside of it,
so the reusable module stays installable anywhere, without a window
system or the vendored library.

## Configuration file format

One `KEY=VALUE` pair per line. Lines starting with `#` are comments and
are ignored.

| Key | Required | Description | Example |
|---|---|---|---|
| `WIDTH` | yes | Maze width, in cells | `WIDTH=20` |
| `HEIGHT` | yes | Maze height, in cells | `HEIGHT=15` |
| `ENTRY` | yes | Entry coordinates `x,y` | `ENTRY=0,0` |
| `EXIT` | yes | Exit coordinates `x,y` | `EXIT=19,14` |
| `OUTPUT_FILE` | yes | Path of the generated output file | `OUTPUT_FILE=maze.txt` |
| `PERFECT` | yes | `True` for exactly one path entry→exit, `False` to allow loops | `PERFECT=True` |
| `SEED` | no | Integer seed for reproducible generation | `SEED=42` |
| `DRAW_PATTERN` | no | Stamp the visible "42" pattern (default `True`) | `DRAW_PATTERN=True` |

Any missing required key, invalid value, out-of-bounds `ENTRY`/`EXIT`, or
malformed line produces a clear error message on the console; the program
never crashes with a raw traceback on bad input.

### Output file format

- One line per maze row, one hexadecimal digit per cell. Bit 0 = North,
  bit 1 = East, bit 2 = South, bit 3 = West; a set bit means the wall is
  closed.
- One empty line.
- Three lines: entry coordinates (`x,y`), exit coordinates (`x,y`), and
  the shortest path from entry to exit as a string of `N`/`E`/`S`/`W`
  letters.

This format was checked against 42's own `tools/output_validator.py`
during development.

## Algorithm

Maze generation uses **randomized recursive backtracking** (an iterative,
stack-based depth-first search over the grid, driven by a seeded random
number generator):

1. Every cell in the grid starts with all four walls closed.
2. Starting at `ENTRY`, the algorithm repeatedly moves to a random
   unvisited neighbour, knocking down the wall between the current and
   the new cell, and pushes the new cell onto a stack. When a cell has no
   unvisited neighbours, it backtracks (pops the stack) until it finds a
   cell that does, or the stack is empty.
3. This produces a **spanning tree** over all non-pattern cells: by
   construction there is exactly one path between any two cells, which is
   precisely what a "perfect" maze requires — no extra validation step is
   needed to guarantee it.
4. If `PERFECT=False`, a bounded number of extra passages are opened
   afterwards (candidate walls are shuffled and opened one at a time,
   each one checked against the corridor-width rule before being kept),
   introducing loops and alternative paths while never creating an open
   area wider than 2 cells.

**Why this algorithm:** recursive backtracking is simple to reason about,
runs in linear time relative to the number of cells, and — because it
builds a spanning tree — automatically satisfies most of the subject's
"hard" requirements (full connectivity, coherent shared walls, closed
outer border, no cycles for perfect mazes, no wide open corridors) as a
side effect of the algorithm itself, rather than needing separate
post-hoc fixes. The main extra logic needed on top is the "42" pattern
(cells excluded from the spanning tree, see below) and, for non-perfect
mazes, the loop-adding pass.

The "42" pattern is drawn by carving out a fixed bitmap of cells (spelling
"42") *before* generation starts and marking them as "blocked": the
spanning-tree algorithm simply never visits or opens walls into them, so
they stay fully closed and isolated, satisfying the pattern requirement
without any special-casing in the core algorithm. If the maze is too
small to fit the pattern (or `ENTRY`/`EXIT` would overlap it), it is
skipped and a warning is printed, as allowed by the subject.

## Reusable code

All maze generation logic lives in the `mazegen_core` package (used by
`a_maze_ing.py`, but with zero dependency on it), and is also distributed
as a standalone pip package, `mazegen-1.0.0-py3-none-any.whl`, built from
the sources in this repository (see `pyproject.toml` and "Build the
reusable package" above). It has no dependency on MLX.

Public API (`from mazegen_core import ...`):

- `MazeGenerator` — the reusable class. Instantiate with `width`,
  `height`, `entry`, `exit_coord`, `perfect`, `seed`, `draw_pattern`, then
  call `.generate()` to obtain a `Maze`.
- `Maze`, `Cell`, `Direction` — the generated data structure. `maze.cell_at((x, y))`
  gives a `Cell`; `cell.has_wall(Direction.NORTH)` etc. inspects it.
- `shortest_path(maze)` — access the solution.
- `validate_maze(maze, perfect_required=...)` and `write_maze(maze, path)`
  — reusable independently of the CLI.

Basic usage example:

```python
from mazegen_core import MazeGenerator

generator = MazeGenerator(
    width=20,
    height=15,
    entry=(0, 0),
    exit_coord=(19, 14),
    perfect=True,   # single path between entry and exit
    seed=42,        # reproducible generation
)

maze = generator.generate()
```

Custom parameters: `width`, `height` (dimensions, required); `entry`,
`exit_coord` (`(x, y)` tuples, must be inside bounds and different);
`perfect` (single path vs. loops allowed); `seed` (optional `int`, same
seed + same parameters = same maze); `draw_pattern` (defaults to `True`,
skipped with a warning in `generator.last_warnings` if the maze is too
small).

Accessing the generated structure:

```python
cell = maze.cell_at((0, 0))          # mazegen_core.cell.Cell
cell.has_wall(Direction.NORTH)        # bool

from mazegen_core import shortest_path
shortest_path(maze)                   # e.g. "EESSN..." (solution)
maze.is_blocked((x, y))               # True if part of the "42" pattern
```

The graphical display (`mlx_renderer.py`, using MLX) is deliberately
**not** part of `mazegen_core` — it lives at the project root instead, so
that the reusable, pip-installable module stays free of the MLX
dependency and works anywhere, with no window system required.

## Resources

- [Wikipedia — Maze generation algorithm](https://en.wikipedia.org/wiki/Maze_generation_algorithm) — overview of recursive backtracking, Kruskal's, Prim's and other approaches.
- [Jamis Buck — "Maze Generation: Algorithm Recap"](https://weblog.jamisbuck.org/2011/2/7/maze-generation-algorithm-recap) — practical comparison and visualisations of maze algorithms.
- [Red Blob Games — Maze generation](https://www.redblobgames.com/) — general grid/graph algorithm reference used while designing the wall/direction model.
- [Python `pyproject.toml` packaging guide](https://packaging.python.org/en/latest/tutorials/packaging-projects/) — used for the `mazegen` pip package setup.
- 42's own `mlx.h` / man pages, bundled inside the `mlx-2.2-py3-*.whl` packages (`mlx/docs/`) — reference for the MLX function signatures used in `mlx_renderer.py`.

**AI usage:** an AI assistant (Claude) was used to review the initial
data-model code (`Cell`, `Direction`, `Maze`) that the team had already
started, identify integration bugs (inconsistent/broken imports across
files), and then implement the remaining modules following the subject's
requirements: the config parser, the recursive-backtracking generator,
the "42" pattern stamping, the maze validator, the BFS solver, the hex
output writer, the CLI entry point, the pip packaging setup, the
automated tests, and this README. The whole codebase was then rewritten,
at the team's request, into a more explicit, C-like style (plain
constructors instead of `@dataclass`, explicit loops instead of
comprehensions, no deferred/lazy imports) to match the team's own
background and existing code. The graphical display was implemented
against the real MLX Python API (inspected directly from the wheel 42
provided) after the terminal-only version was replaced. All generated
code was run and checked against `pytest`, `flake8`, and
`mypy --strict` before being included; the maze output format was also
checked against 42's own `tools/output_validator.py`.

## Team and project management

| Login | Role |
|---|---|
| `diemonte` | Core data model (`Cell`, `Direction`, `Maze`), project integration |
| `jfaria-c` | Initial maze navigation / neighbour-traversal logic |

**Planning:** the project started with the shared data structures
(`Cell`, `Direction`, `Maze`) and a first pass at neighbour traversal.
Generation, validation, solving, output formatting, the CLI, packaging,
and documentation were then built on top of that foundation to complete
the mandatory part end to end; the terminal display was later replaced
with a graphical MLX window.

**What worked well:** designing the wall/direction bit values
(`N=1, E=2, S=4, W=8`) and the symmetric `open_between()` helper early on
made every later requirement (hex output, coherent shared walls, closed
borders) fall out naturally instead of needing special-case checks.
Keeping the MLX-specific code outside of `mazegen_core` also meant the
reusable module never had to depend on a window system or a vendored
library.

**What could be improved:** the two initial modules were written with
inconsistent import conventions (absolute vs. relative vs. a
non-existent package name), which had to be reconciled before the rest of
the package could be built on top — agreeing on a package layout up front
would have saved that cleanup pass.

**Tools used:** Python 3, `pytest`, `flake8`, `mypy`, `build` (PyPA), Git/GitHub, 42's `mlx` Python package and `output_validator.py`.
