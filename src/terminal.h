#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>

// terminal_t stores our terminal
// settings and allows us to use
// raw mode for text processing.
typedef struct
{
    int file_descriptor;
    struct termios original_settings;
    struct termios raw_settings;
} terminal_t;

terminal_t *terminal_create(int file_descriptor);
void enable_raw_mode(terminal_t *term);
void disable_raw_mode(terminal_t *term);

#endif /* TERMINAL_H */
