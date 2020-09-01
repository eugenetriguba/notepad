#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "notepad.h"

int main(int argc, char *argv[]) {
    notepad_t *notepad = notepad_create(STDIN_FILENO);

    for (int i = 0; i < argc; i++) {
        if ((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "--debug") == 0)) {
            notepad->debug_mode = 1;
            printf("Notepad debug mode is on.\r\n");
        }
    }

    return startup_notepad_app(notepad);
}
