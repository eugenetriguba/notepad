#include <ctype.h>
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
    int debug_mode;
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
    notepad->debug_mode = 0;

    return notepad;
}

void notepad_destroy(notepad_t *notepad)
{
    disable_raw_mode(notepad);
    free(notepad);
}

void read_all_bytes(notepad_t *notepad)
{
    char tmp;

    while(read(notepad->file_descriptor, &tmp, 1) == 1)
    {
	if (notepad->debug_mode)
	{
	    iscntrl(tmp) ? 
		printf("%d\n", tmp) : 
		printf("%d ('%c')\n", tmp, tmp);
	}
	
	if (tmp == 'q') 
	{
	    return;
	}

        strcat(notepad->contents, &tmp);
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
    notepad->debug_mode = 1;

    if (notepad->debug_mode)
    {
	printf("Notepad debug mode is on!\n");
    }

    read_all_bytes(notepad);
    
    printf("%s\n", notepad->contents);

    notepad_destroy(notepad);
    return 0;
}

int main() 
{
    return startup_notepad_app(notepad_create(STDIN_FILENO));
}

