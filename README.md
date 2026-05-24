*This project has been created as part of the 42 curriculum by romdo-na.*

# get_next_line

> Reading a line from a file descriptor is way too tedious.

---

## Description

**get_next_line** is a project from the [42 School](https://www.42porto.com/) curriculum. The goal is to implement a function in C that reads from a file descriptor and returns one line at a time on each successive call. When there is nothing left to read, or if an error occurs, the function returns `NULL`.

The returned line includes the terminating `\n` character, except when the end of file is reached and the file does not end with `\n`. The function must work both when reading from a regular file and from the standard input.

**Core concept:** static variables — used to preserve unread data between successive calls without relying on global variables (which are forbidden).

**Function signature:**

| Field             | Value                                                              |
|-------------------|--------------------------------------------------------------------|
| Function Name     | `get_next_line`                                                    |
| Prototype         | `char *get_next_line(int fd);`                                     |
| Files to submit   | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h`     |
| Parameter         | `fd` — the file descriptor to read from                           |
| Return value      | The line read on success; `NULL` on end-of-file or error          |
| External functions| `read`, `malloc`, `free`                                           |

**Forbidden:** `libft`, `lseek()`, global variables.

---

## Algorithm

The implementation uses a **single static variable** (`stash`) that persists across calls to hold any content read from the file descriptor beyond the current line.

### Step-by-step

**1. Read and accumulate — `read_and_save()`**
The function reads `BUFFER_SIZE` bytes at a time from `fd` and appends each chunk to `stash` using `ft_strjoin`. This loop continues until a `\n` is found inside `stash`, or until `read()` returns 0 (end of file) or -1 (error). On error, both the buffer and `stash` are freed and `NULL` is returned.

**2. Extract the line — `extract_line()`**
Once `stash` contains a complete line (or the last remaining content), the function scans for the first `\n` and allocates a new string with everything up to and including it.

**3. Clean the stash — `clean_stash()`**
Everything after the extracted line's `\n` is preserved in a new `stash` for the next call. If nothing remains, `stash` is freed and set to `NULL`.

### Justification

Reading `BUFFER_SIZE` bytes at a time balances efficiency and correctness:
- Reading byte-by-byte (BUFFER_SIZE=1) would be correct but very slow due to the overhead of one `read()` syscall per character.
- Reading the whole file at once would be wasteful in memory and would violate the subject's instruction to "read as little as possible each time `get_next_line()` is called."
- The stash approach ensures that even if `read()` returns more than one line in a single call, no data is lost between calls.

The function handles edge cases correctly regardless of `BUFFER_SIZE`:
- `BUFFER_SIZE=1` — reads one byte at a time, many iterations, still correct.
- `BUFFER_SIZE=9999` or larger — may read the entire file in one call, still correct because excess data is preserved in `stash`.
- Files whose last line has no `\n` — handled by returning the remaining content without a trailing newline.
- Invalid `fd` or `BUFFER_SIZE ≤ 0` — validated upfront; `stash` is freed and `NULL` is returned.

---

## Instructions

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

The `BUFFER_SIZE` macro defines how many bytes are read per `read()` call. It can be any positive integer and will be adjusted by peer evaluators and the Moulinette during testing. The project must also compile without the flag (a default value is defined in the header):

```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
```

### Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char  *line;

    fd = open("text.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### File structure

```
get_next_line/
├── get_next_line.c          # Main function and core reading logic
├── get_next_line_utils.c    # Helper functions (ft_strjoin, ft_strchr, ft_strdup...)
├── get_next_line.h          # Header — prototype and BUFFER_SIZE default
├── main.c                   # Test file (not graded)
└── text.txt                 # Sample text file for testing
```

---

## Resources

- [Static variables in C — GeeksforGeeks](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors — Wikipedia](https://en.wikipedia.org/wiki/File_descriptor)
- [`read()` system call — Linux man page](https://man7.org/linux/man-pages/man2/read.2.html)
- [Memory management in C — cppreference](https://en.cppreference.com/w/c/memory/malloc)
- [42 Norm documentation](https://github.com/42School/norminette)

**AI usage:**
AI was not used to write or debug the source code of this project, in accordance with 42's foundational phase guidelines on independent learning. AI (Claude) was used exclusively to help structure and write this README file — specifically to organise the required sections and review phrasing.