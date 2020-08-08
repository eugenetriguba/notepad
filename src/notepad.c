#include "notepad.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "terminal.h"

// notepad_create is what initializes our notepad_t
// and starts up the terminal settings in raw mode.
//
// Args:
//   file_descriptor: The descriptor for where to read from.
//   e.g. STDIN_FILENO from <unistd.h>
//
// Returns:
//   An initialized notepad_t or NULL if our malloc call failed.
notepad_t *notepad_create(int file_descriptor)
{
    notepad_t *notepad = malloc(sizeof(notepad_t));
    if (notepad == NULL)
    {
        return NULL;
    }

    notepad->file_descriptor = file_descriptor;
    notepad->terminal = terminal_create(file_descriptor);
    notepad->debug_mode = 0;

    enable_raw_mode(notepad->terminal);

    return notepad;
}

// notepad_destroy tears down the notepad_t
// by disabling raw mode so the user does
// not have the disabled terminal flags leak
// into theirs and frees the memory for the
// notepad_t.
//
// Args:
//   notepad: An initialized notepad_t.
void notepad_destroy(notepad_t *notepad)
{
    disable_raw_mode(notepad->terminal);
    free(notepad);
}

// read_all_bytes reads in all the bytes
// coming from the notepad's file descriptor
// and places those characters into the notepad's
// contents.
//
// If a 'q' is read in, we exit the program. If the
// notepad is in it's debug mode, each character's
// ascii code is printed and, unless it is a control
// character, it's character representation.
//
// Args:
//   notepad: An initialized notepad_t.
void read_all_from_fd(notepad_t *notepad)
{
    char tmp;

    while (1)
    {
        tmp = '\0';
        read(notepad->file_descriptor, &tmp, 1);

        if (notepad->debug_mode && tmp != '\0')
        {
            iscntrl(tmp) ? printf("%d\r\n", tmp)
                         : printf("%d ('%c')\r\n", tmp, tmp);
        }

        if (tmp == 'q')
        {
            break;
        }

        strcat(notepad->contents, &tmp);
    }
}

// startup_notepad_app runs our notepad
// by reading in all the bytes from the
// file descriptor, printing them out,
// and destroying the notepad.
//
// Args:
//   notepad: An initialized notepad_t.
//
// Returns:
//   0, for the exit code for main().
int startup_notepad_app(notepad_t *notepad)
{
    read_all_from_fd(notepad);
    printf("%s\r\n", notepad->contents);
    notepad_destroy(notepad);

    return 0;
}
