#include "notepad.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

// notepad_create is what initializes our notepad_t.
//
// Args:
//   file_descriptor: The descriptor for where to read from.
//   e.g. STDIN_FILENO from <unistd.h>
//
// Returns:
//   An initialized notepad_t or NULL if our malloc call failed.
notepad_t *notepad_create(int file_descriptor) {
    notepad_t *notepad = malloc(sizeof(notepad_t));
    if (notepad == NULL) {
	return NULL;
    }

    notepad->file_descriptor = file_descriptor;
    enable_raw_mode(notepad);
    notepad->debug_mode = 0;

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
void notepad_destroy(notepad_t *notepad) {
    disable_raw_mode(notepad);
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
void read_all_bytes(notepad_t *notepad) {
    char tmp;

    while (1) {
	tmp = '\0';
	read(notepad->file_descriptor, &tmp, 1);

	if (notepad->debug_mode && tmp != '\0') {
	    iscntrl(tmp) ? printf("%d\n", tmp)
			 : printf("%d ('%c')\n", tmp, tmp);
	}

	if (tmp == 'q') {
	    break;
	}

	strcat(notepad->contents, &tmp);
    }
}

// enable_raw_mode enables a sort of "raw mode"
// for the notepad. There is no "raw mode" persay
// that we can turn off and on. What we do is turn
// off a variety of flags that have to do with features
// that process the text for us in various ways.
//
// The original settings are saved into the notepad's
// orig field for when we want to disable the mode.
//
// Furthermore, a timeout is setup for read() calls
// so the read() call is not blocking us from doing
// something else on the screen.
//
// Args:
//   notepad: An initialized notepad_t.
void enable_raw_mode(notepad_t *notepad) {
    tcgetattr(notepad->file_descriptor, &notepad->orig);

    notepad->raw = notepad->orig;
    notepad->raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    notepad->raw.c_oflag &= ~(OPOST);
    notepad->raw.c_cflag |= (CS8);
    notepad->raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);

    // min number of bytes needed for read() before it can return
    notepad->raw.c_cc[VMIN] = 0;
    // max time to wait before read() can return (in tenths of a sec)
    notepad->raw.c_cc[VTIME] = 1;

    tcsetattr(notepad->file_descriptor, TCSAFLUSH, &notepad->raw);
}

// disable_raw_mode sets our notepad's file
// descriptor settings back to the original
// ones.
//
// Args:
//   notepad: An initialized notepad_t.
void disable_raw_mode(notepad_t *notepad) {
    tcsetattr(notepad->file_descriptor, TCSAFLUSH, &notepad->orig);
}

// startup_notepad_app runs our notepad
// by reading in all the bytes from the
// file descriptor, printing them out,
// and destroying the notepad.
//
// Args:
//   notepad: An initialized notepad_t.
int startup_notepad_app(notepad_t *notepad) {
    read_all_bytes(notepad);
    printf("%s\n", notepad->contents);
    notepad_destroy(notepad);

    return 0;
}

