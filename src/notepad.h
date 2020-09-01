#ifndef NOTEPAD_H
#define NOTEPAD_H

#include "terminal.h"

// notepad_t represents our notepad
// with what file descriptor we are
// reading from, a terminal_t so we can
// alter the terminal's settings, and we
// are in our notepad's debug mode, and
// our notepad contents.
typedef struct {
    terminal_t *terminal;
    int file_descriptor;
    char contents[1024];
    int debug_mode;
} notepad_t;

notepad_t *notepad_create(int file_descriptor);
void notepad_destroy(notepad_t *notepad);
void read_all_from_fd(notepad_t *notepad);
char read_notepad_key(notepad_t *notepad);
int process_notepad_keypress(notepad_t *notepad);

int startup_notepad_app(notepad_t *notepad);

#endif /* NOTEPAD_H */
