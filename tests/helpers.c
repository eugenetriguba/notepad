#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../src/notepad.h"

notepad_t *create_test_notepad(char *contents) {
    FILE *tmp = tmpfile();
    int fd = fileno(tmp);
    
    if (write(fd, &contents, sizeof(contents)) == -1) {
	printf("writing %s to temp file failed.\n", contents);
	exit(1);
    }

    return notepad_create(fd);
}
