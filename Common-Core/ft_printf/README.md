*This project has been created as part of the 42 curriculum by diemonte.*

# ft_printf

## Description

The ft_printf project is a reimplementation of the standard C library function printf.

The goal of this project is to understand and reproduce the behavior of printf, including formatted output, variadic functions, and type handling in C.

This project focuses on:
- Variadic functions (stdarg.h)
- Parsing format strings
- Handling different data types
- Output formatting to standard output
- Memory and error handling

Supported conversions:
- %c → character
- %s → string
- %p → pointer
- %d / %i → integers
- %u → unsigned integers
- %x / %X → hexadecimal
- %% → percent sign

## Instructions

### Compilation

To compile the library:

```
make
```

This will generate the static library:

```
libftprintf.a
```

### Usage

To use ft_printf in another project:

```
gcc main.c -L. -lftprintf
```

Or include it in your Makefile:

```
LIBS = -L. -lftprintf
```

Include the header:

```c
#include "ft_printf.h"
```

## Algorithm and Data Structure Justification

### Data Structures Used

- **Strings (char \*):** Used for parsing format strings and handling outputs.
- **Variadic arguments (stdarg.h):** Used to handle a variable number of arguments.
- **Basic integer types:** Used for number conversions.

No advanced data structures are required for this project.

### Algorithmic Approach

The implementation is based on linear parsing of the format string.

Main steps:
1. Iterate through the format string.
2. Detect `%` characters.
3. Identify the conversion specifier.
4. Retrieve the argument using `va_arg`.
5. Convert and print the value.

The `ft_printf` main loop runs in O(n). Number conversion functions convert integers digit by digit recursively. Parsing is done in a simple state-based manner.

## Complexity Analysis

- String traversal: O(n)
- Number conversions: O(d), where d is the number of digits
- Overall complexity: O(n)

## Resources

- `man 3 printf`
- `man stdarg`
- https://www.geeksforgeeks.org/variadic-functions-in-c/
- https://en.cppreference.com/w/c/io/fprintf
- https://www.tutorialspoint.com/c_standard_library/

## AI Usage

AI was used to:
- Clarify printf behavior and format specifiers
- Structure README according to 42 requirements
- Explain variadic functions and complexity
- Improve documentation clarity

All code was written manually and tested according to 42 rules.
