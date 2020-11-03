#include "terminal.h"

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>

#include "utils.h"

/**
 * terminal_create initializes our terminal_t.
 *
 * The current file_descriptors tc settings are set
 * to original_settings and a raw mode is setup to
 * raw_settings.
 *
 * Args:
 *   file_descriptor: The descriptor for where to
 *   retrieve settings and set terminal settings.
 *
 *   e.g. STDIN_FILENO from <unistd.h>
 *
 * Returns:
 *   An initialized terminal_t or NULL if the malloc call failed.
 */
terminal_t *terminal_create(int file_descriptor) {
    terminal_t *term = malloc(sizeof(terminal_t));
    if (term == NULL) {
        return NULL;
    }

    term->file_descriptor = file_descriptor;

    if (tcgetattr(term->file_descriptor, &term->original_settings) == -1) {
        err_exit("terminal_create (tcgetattr)");
    }

    term->raw_settings = term->original_settings;
    term->raw_settings.c_iflag &=
        ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    term->raw_settings.c_oflag &= ~(OPOST);
    term->raw_settings.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    term->raw_settings.c_cflag &= ~(CSIZE | PARENB);
    term->raw_settings.c_cflag |= (CS8);

    // min number of bytes needed for read() before it can return
    term->raw_settings.c_cc[VMIN] = 0;
    // max time to wait before read() can return (in tenths of a sec)
    term->raw_settings.c_cc[VTIME] = 1;

    return term;
}

/**
 * enable_raw_mode sets the term's raw_settings
 * to be the current file_descriptor's settings.
 */
void enable_raw_mode(terminal_t *term) {
    if (tcsetattr(term->file_descriptor, TCSAFLUSH, &term->raw_settings) == -1) {
        err_exit("enable_raw_mode (tcsetattr)");
    }
}

/**
 * disable_raw_mode sets the term's original settings
 * to be the current file_descriptor's settings.
 */
void disable_raw_mode(terminal_t *term) {
    if (tcsetattr(term->file_descriptor, TCSAFLUSH, &term->original_settings) == -1) {
        err_exit("disable_raw_mode (tcsetattr)");
    }
}
