#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <termios.h>

// notepad_t represents our notepad
// with what file descriptor we are
// reading from, termios settings for
// our original settings and raw mode
// settings, and we are in our notepad's
// debug mode, and our notepad contents.
typedef struct notepad_t {
    int file_descriptor;
    struct termios orig;
    struct termios raw;
    char contents[1024];
    int debug_mode;   
} notepad_t;

notepad_t *notepad_create(int file_descriptor);
void notepad_destroy(notepad_t *notepad);
void enable_raw_mode(notepad_t *notepad);
void disable_raw_mode(notepad_t *notepad);
void read_all_bytes(notepad_t *notepad);

int startup_notepad_app(notepad_t *notepad);

#endif /* NOTEPAD_H */
