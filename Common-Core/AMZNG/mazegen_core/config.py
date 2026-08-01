"""Parser for a_maze_ing.py's configuration file.

The configuration file uses one 'KEY=VALUE' pair per line. Lines starting
with '#' are comments and are ignored.

Required keys: WIDTH, HEIGHT, ENTRY, EXIT, OUTPUT_FILE, PERFECT.
Optional keys: SEED, DRAW_PATTERN.
"""

from __future__ import annotations

from pathlib import Path

_TRUE_VALUES = {"true", "1", "yes", "y"}
_FALSE_VALUES = {"false", "0", "no", "n"}

_REQUIRED_KEYS = ("WIDTH", "HEIGHT", "ENTRY", "EXIT", "OUTPUT_FILE", "PERFECT")


class ConfigError(Exception):
    """Raised when the configuration file is missing, malformed or invalid."""


class MazeConfig:

    # Guarda todos os valores já lidos e validados do ficheiro de config.
    def __init__(
        self,
        width: int,
        height: int,
        entry: tuple,
        exit: tuple,
        output_file: str,
        perfect: bool,
        seed: int | None,
        draw_pattern: bool,
    ) -> None:

        self.width = width
        self.height = height
        self.entry = entry
        self.exit = exit
        self.output_file = output_file
        self.perfect = perfect
        self.seed = seed
        self.draw_pattern = draw_pattern


# Lê e valida um ficheiro de configuração no formato KEY=VALUE.
# Nunca deixa passar um erro sem tratar: tudo vira ConfigError com
# uma mensagem clara para o utilizador.
def load_config(path: str) -> MazeConfig:

    raw_lines = _read_lines(path)
    values = _parse_lines(raw_lines, path)
    _check_required_keys(values, path)

    width = _parse_positive_int(values, "WIDTH", path)
    height = _parse_positive_int(values, "HEIGHT", path)
    entry = _parse_coordinate(values, "ENTRY", path)
    exit_coord = _parse_coordinate(values, "EXIT", path)
    output_file = _parse_output_file(values, path)
    perfect = _parse_bool(values, "PERFECT", path)
    seed = _parse_optional_int(values, "SEED", path)
    draw_pattern = _parse_optional_bool(values, "DRAW_PATTERN", path, True)

    _check_bounds(entry, "ENTRY", width, height, path)
    _check_bounds(exit_coord, "EXIT", width, height, path)

    if entry == exit_coord:
        raise ConfigError(f"{path}: ENTRY and EXIT must be different cells.")

    config = MazeConfig(
        width=width,
        height=height,
        entry=entry,
        exit=exit_coord,
        output_file=output_file,
        perfect=perfect,
        seed=seed,
        draw_pattern=draw_pattern,
    )

    return config


# Lê o ficheiro linha a linha, devolvendo uma lista de strings.
def _read_lines(path: str) -> list:

    file_path = Path(path)

    if not file_path.exists():
        raise ConfigError(f"Configuration file not found: {path}")

    if not file_path.is_file():
        raise ConfigError(f"Not a regular file: {path}")

    try:
        text = file_path.read_text(encoding="utf-8")
    except OSError as error:
        raise ConfigError(f"Could not read configuration file {path}: {error}") from error
    except UnicodeDecodeError as error:
        raise ConfigError(f"Configuration file {path} is not valid UTF-8 text: {error}") from error

    lines = text.splitlines()

    return lines


# Percorre cada linha e guarda os pares KEY=VALUE num dicionário.
def _parse_lines(lines: list, path: str) -> dict:

    values = {}
    line_number = 0

    for raw_line in lines:

        line_number = line_number + 1
        line = raw_line.strip()

        if line == "":
            continue

        if line.startswith("#"):
            continue

        if "=" not in line:
            raise ConfigError(
                f"{path}:{line_number}: invalid syntax, expected KEY=VALUE: '{raw_line}'"
            )

        key, _, value = line.partition("=")
        key = key.strip().upper()
        value = value.strip()

        if key == "":
            raise ConfigError(f"{path}:{line_number}: empty key in '{raw_line}'")

        values[key] = value

    return values


# Verifica se todas as chaves obrigatórias estão presentes.
def _check_required_keys(values: dict, path: str) -> None:

    missing = []

    for key in _REQUIRED_KEYS:
        if key not in values:
            missing.append(key)

    if len(missing) > 0:
        raise ConfigError(f"{path}: missing required key(s): {', '.join(missing)}")


def _parse_positive_int(values: dict, key: str, path: str) -> int:

    raw = values[key]

    try:
        number = int(raw)
    except ValueError as error:
        raise ConfigError(f"{path}: {key} must be an integer, got '{raw}'") from error

    if number <= 0:
        raise ConfigError(f"{path}: {key} must be a positive integer, got {number}")

    return number


def _parse_optional_int(values: dict, key: str, path: str) -> int | None:

    if key not in values:
        return None

    if values[key] == "":
        return None

    raw = values[key]

    try:
        number = int(raw)
    except ValueError as error:
        raise ConfigError(f"{path}: {key} must be an integer, got '{raw}'") from error

    return number


def _parse_coordinate(values: dict, key: str, path: str) -> tuple:

    raw = values[key]
    parts = raw.split(",")

    if len(parts) != 2:
        raise ConfigError(f"{path}: {key} must be in the form 'x,y', got '{raw}'")

    try:
        x = int(parts[0].strip())
        y = int(parts[1].strip())
    except ValueError as error:
        raise ConfigError(f"{path}: {key} coordinates must be integers, got '{raw}'") from error

    if x < 0 or y < 0:
        raise ConfigError(f"{path}: {key} coordinates must be non-negative, got '{raw}'")

    return (x, y)


def _parse_output_file(values: dict[str, str], path: str) -> str:

    raw = values["OUTPUT_FILE"]

    if raw == "":
        raise ConfigError(f"{path}: OUTPUT_FILE must not be empty.")

    return raw


def _parse_bool(values: dict, key: str, path: str) -> bool:

    raw = values[key].strip().lower()

    if raw in _TRUE_VALUES:
        return True

    if raw in _FALSE_VALUES:
        return False

    raise ConfigError(f"{path}: {key} must be a boolean (True/False), got '{values[key]}'")


def _parse_optional_bool(values: dict, key: str, path: str, default: bool) -> bool:

    if key not in values:
        return default

    if values[key] == "":
        return default

    raw = values[key].strip().lower()

    if raw in _TRUE_VALUES:
        return True

    if raw in _FALSE_VALUES:
        return False

    raise ConfigError(f"{path}: {key} must be a boolean (True/False), got '{values[key]}'")


def _check_bounds(coord: tuple, key: str, width: int, height: int, path: str) -> None:

    x = coord[0]
    y = coord[1]

    if x >= width or y >= height:
        raise ConfigError(
            f"{path}: {key} {coord} is outside the maze bounds "
            f"(WIDTH={width}, HEIGHT={height})."
        )
