*This project has been created as part of the 42 curriculum by diemonte.*

# get_next_line

## Description

`get_next_line` is a C function that reads a single line at a time from a file descriptor. Each call to the function returns the next line from the file, including the terminating `\n` character (except when the end of file is reached and the file does not end with `\n`). When there is nothing left to read, or an error occurs, it returns `NULL`.

The main goal of the project is to understand how persistent state can be maintained between function calls using **static variables**, while also improving knowledge of:

- File descriptors
- Dynamic memory allocation
- Buffer management
- String manipulation
- Efficient reading strategies in C

This implementation uses a **dynamic stash buffer** to preserve unread data between calls. Instead of rebuilding the line from scratch every time, the function accumulates data in a persistent buffer, extracts one line, and shifts the remaining content for the next call.

The bonus part extends the mandatory implementation to support **multiple file descriptors simultaneously**, allowing the function to read from different files without losing track of each one's reading state.

---

## Algorithm

The implementation uses a **dynamic buffer (stash)** as its core data structure.

### Why a dynamic stash buffer?

The `read()` system call reads a fixed number of bytes at a time (defined by `BUFFER_SIZE`). A line in a file may be longer or shorter than `BUFFER_SIZE`, so multiple reads may be needed before a `\n` is found.

To handle this efficiently, the implementation stores all unread data inside a dynamically allocated buffer called the **stash**. The stash grows automatically when more space is needed and persists between function calls through a `static` structure.

This approach avoids repeatedly allocating small chunks and simplifies memory management compared to linked list implementations.

### Detailed algorithm explanation

1. **Persistent state using `static`**

   A static `t_gnl` structure is used to preserve unread data between calls to `get_next_line`. This allows the function to continue reading exactly where the previous call stopped.

2. **Reading into a temporary buffer**

   `gnl_read_to_stash` allocates a temporary buffer of size `BUFFER_SIZE` and repeatedly calls `read()` until:

   - A newline (`\n`) is found
   - End of file is reached
   - An error occurs

3. **Appending data to the stash**

   Newly read bytes are appended to the stash using `gnl_append`. Before copying data, `gnl_grow` ensures enough memory is available.

4. **Dynamic growth strategy**

   Instead of reallocating memory byte-by-byte, the stash capacity grows exponentially (`64 -> 128 -> 256 -> ...`). This significantly improves performance by reducing the number of allocations.

5. **Extracting the next line**

   `gnl_make_line` calculates the exact line length using `gnl_line_len`, allocates the required memory, copies the line, and returns it.

6. **Preserving remaining data**

   After a line is returned, `gnl_shift` moves all unread bytes to the beginning of the stash so they are available during the next function call.

7. **Memory safety**

   The implementation includes:

   - Overflow protection during allocations
   - Proper freeing of allocated memory
   - NULL checks
   - Safe handling of invalid file descriptors and invalid `BUFFER_SIZE` values

### Bonus — multiple file descriptors

For the bonus, instead of a single static structure:

```c
static t_gnl gnl;
```

An array indexed by file descriptor can be used:

```c
static t_gnl gnl[4096];
```

Each file descriptor maintains its own independent stash, allowing simultaneous reading from multiple files without mixing states.

---

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl
```

You can replace `42` with any positive integer as the buffer size.

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Files

| File | Description |
|---|---|
| `get_next_line.c` | Main function and buffer management |
| `get_next_line_utils.c` | Utility functions for stash manipulation |
| `get_next_line.h` | Header file with prototypes and struct |
| `get_next_line_bonus.c` | Bonus — multiple fd support |
| `get_next_line_utils_bonus.c` | Bonus — utility functions |
| `get_next_line_bonus.h` | Bonus — header file |

---

## Resources

### Documentation and references

- GNU C Library — `read()`
  https://man7.org/linux/man-pages/man2/read.2.html

- Static variables in C — GeeksforGeeks
  https://www.geeksforgeeks.org/static-variables-in-c/

- Dynamic memory allocation in C — `malloc` and `free`
  https://man7.org/linux/man-pages/man3/malloc.3.html

- Buffer management and dynamic arrays
  https://stackoverflow.com/questions/20448031/is-doubling-the-capacity-of-a-dynamic-array-necessary

- File descriptors in Unix systems
  https://man7.org/linux/man-pages/man2/open.2.html

### AI Usage

AI tools were used strictly as learning support resources during the development of this project.

Claude (Anthropic) was used to:

- Explain how `static` variables persist between function calls
- Clarify pointer behaviour and memory management concepts
- Understand dynamic buffers and stash-based implementations
- Walk through the control flow between functions
- Discuss buffer growth strategies and memory safety

The AI was used exclusively for conceptual explanations and debugging guidance.

All code was written, reviewed, and fully understood by the author.
