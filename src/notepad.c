#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "notepad.h"

struct notepad_t
{
    int file_descriptor;
    struct termios raw;
    char contents[1024];
};

notepad_t *notepad_create(int file_descriptor)
{
    notepad_t *notepad = malloc(sizeof(notepad_t));
    if (notepad == NULL)
    {
	return NULL;
    }

    notepad->file_descriptor = file_descriptor;
    enable_raw_mode(notepad);

    return notepad;
}

void notepad_destroy(notepad_t *notepad)
{
    disable_raw_mode(notepad);
    free(notepad);
}

void read_all_bytes(notepad_t *notepad)
{
    char tmp[2];
    int i;

    while(read(notepad->file_descriptor, &tmp, 1) == 1)
    {
	for (i = 0; i < 2; i++)
	{
	    if (tmp[i] == 'q') return;
	}

        strcat(notepad->contents, tmp);	
    }
}

void enable_raw_mode(notepad_t *notepad)
{
    tcgetattr(notepad->file_descriptor, &notepad->raw);

    notepad->raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(notepad->file_descriptor, TCSAFLUSH, &notepad->raw);
}

void disable_raw_mode(notepad_t *notepad)
{
    tcsetattr(notepad->file_descriptor, TCSAFLUSH, &notepad->raw);
}

int startup_notepad_app(notepad_t *notepad)
{
    read_all_bytes(notepad);
    
    printf("%s\n", notepad->contents);

    notepad_destroy(notepad);
    return 0;
}

int main() 
{
    return startup_notepad_app(notepad_create(STDIN_FILENO));
}

