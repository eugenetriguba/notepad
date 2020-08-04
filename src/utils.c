#include <stdio.h>
#include <stdlib.h>


void err_exit(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}
