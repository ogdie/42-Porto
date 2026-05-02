*This project has been created as part of the 42 curriculum by diemonte.*

# Libft

## Description
Libft is a custom C static library (libft.a) that reimplements a subset of the C standard library (libc) functions, along with additional utility functions and a linked list API.  
The goal of this project is to deeply understand how standard functions work by recreating them from scratch and building a reusable personal library for future projects at 42.

This library includes:
- Character and string manipulation functions
- Memory handling functions
- Conversion utilities
- File descriptor output functions
- Singly linked list management functions

## Instructions

### Compilation
To compile the library, run:

```bash
make
```

This will generate the static library:
```
libft.a
```

### Makefile rules
- `make` / `all` → compile the library  
- `clean` → remove object files  
- `fclean` → remove object files and libft.a  
- `re` → full rebuild  

### Usage
Include the header in your project:
```c
#include "libft.h"
```

Compile your project with:
```bash
gcc your_files.c libft.a -o your_program
```

## Library Content

### 1. Libc Functions
Reimplementation of standard C functions:
- isalpha, isdigit, isalnum, isascii, isprint
- strlen, memset, bzero, memcpy, memmove
- strlcpy, strlcat, toupper, tolower
- strchr, strrchr, strncmp, memchr, memcmp, strnstr, atoi
- calloc, strdup

### 2. Additional Functions
Utility functions not included in libc:
- ft_substr
- ft_strjoin
- ft_strtrim
- ft_split
- ft_itoa
- ft_strmapi
- ft_striteri
- ft_putchar_fd
- ft_putstr_fd
- ft_putendl_fd
- ft_putnbr_fd

### 3. Linked List Functions
A custom singly linked list implementation:
- ft_lstnew
- ft_lstadd_front
- ft_lstsize
- ft_lstlast
- ft_lstadd_back
- ft_lstdelone
- ft_lstclear
- ft_lstiter
- ft_lstmap

## Resources

### Documentation & References
- man pages (man 3 libc functions)
- https://en.cppreference.com/
- https://www.gnu.org/software/libc/manual/
- 42 school libft subject PDF
- BSD vs GNU libc differences (for strlcpy/strlcat behavior)

### AI Usage
AI tools were used for:
- Structuring the README.md file
- Improving clarity and formatting of documentation
- Proofreading and ensuring compliance with project requirements

No AI was used to directly generate or replace implementation code for the project functions.

## Notes
This library follows strict 42 rules:
- No global variables
- No memory leaks
- Compilation with -Wall -Wextra -Werror
- Only allowed functions used per specification
