#include <stdio.h>
#include <stdlib.h>

/**
 * Uses perror to print the message
 * and exits the program with a failure.
 *
 * Args:
 *   message: The error message to exit with.
 */
void err_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}
