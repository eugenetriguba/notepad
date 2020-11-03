#include "notepad.h"

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include "keys.h"
#include "terminal.h"
#include "utils.h"

/**
 * notepad_create is what initializes our notepad_t
 * and starts up the terminal settings in raw mode.
 *
 * Args:
 *   file_descriptor: The descriptor for where to read from.
 *   e.g. STDIN_FILENO from <unistd.h>
 *
 * Returns:
 *   An initialized notepad_t or NULL if our malloc call failed.
 */
notepad_t *notepad_create(int file_descriptor) {
    notepad_t *notepad = malloc(sizeof(notepad_t));
    if (notepad == NULL) {
        return NULL;
    }

    notepad->file_descriptor = file_descriptor;
    notepad->terminal = terminal_create(file_descriptor);
    notepad->debug_mode = 0;

    enable_raw_mode(notepad->terminal);

    return notepad;
}

/**
 * notepad_destroy tears down the notepad_t
 * by disabling raw mode so the user does
 * not have the disabled terminal flags leak
 * into theirs and frees the memory for the
 * notepad_t.
 *
 * Args:
 *   notepad: An initialized notepad_t.
 */
void notepad_destroy(notepad_t *notepad) {
    disable_raw_mode(notepad->terminal);
    free(notepad);
}

/**
 * read_all_bytes reads in all the bytes
 * coming from the notepad's file descriptor
 * and places those characters into the notepad's
 * contents.
 *
 * If ctrl-q is read in, we exit the program. If the
 * notepad is in it's debug mode, each character's
 * ascii code is printed and, unless it is a control
 * character, it's character representation.
 *
 * Args:
 *   notepad: An initialized notepad_t.
 */
void read_all_from_fd(notepad_t *notepad) {
    int status = 1;

    do {
        status = process_notepad_keypress(notepad);
    } while (status != 0);
}

/**
 * Processes a notepad keypress by reading one in,
 * checking if it is the quit key, and adding that
 * key to the notepad's contents if not.
 *
 * Furthermore, if the notepad is in debug mode,
 * we print out each key that is pressed.
 *
 * Args:
 *   notepad: The notepad to process keys for.
 *
 * Returns:
 *   0 if we should quit the program; 1 otherwise.
 */
int process_notepad_keypress(notepad_t *notepad) {
    char key = read_notepad_key(notepad);

    if (notepad->debug_mode && key != '\0') {
        iscntrl(key) ? printf("%d\r\n", key) : printf("%d ('%c')\r\n", key, key);
    }

    switch (key) {
    case CTRL_KEY('q'):
        return 0;
        break;
    }

    strcat(notepad->contents, &key);
    return 1;
}

/**
 * Read a single key from the given notepad.
 *
 * Args:
 *   notepad: The notepad to read a key from.
 *
 * Exits:
 *   If an error occurred during the read()
 *
 * Returns:
 *   The key read in from the notepad file descriptor.
 */
char read_notepad_key(notepad_t *notepad) {
    char key;
    int num_read = 0;

    while ((num_read = read(notepad->file_descriptor, &key, 1)) != 1) {
        if (num_read == -1 && errno != EAGAIN) {
            err_exit("read_notepad_key read()\n");
        }
    }

    return key;
}

/**
 * startup_notepad_app runs our notepad by reading in
 * all the bytes from the file descriptor, printing them out,
 * and destroying the notepad.
 *
 * Args:
 *   notepad: An initialized notepad_t.
 *
 * Returns:
 *   0, for the exit code for main().
 */
int startup_notepad_app(notepad_t *notepad) {
    printf("Welcome to notepad! Press ctrl-q to quit.\r\n");

    read_all_from_fd(notepad);
    printf("%s\r\n", notepad->contents);
    notepad_destroy(notepad);

    return 0;
}
