#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../src/notepad.h"

notepad_t *create_test_notepad(char *contents) {
    FILE *tmp = tmpfile();
    int fd = fileno(tmp);

    if (fwrite(contents, strlen(contents) + 1, 1, tmp) == -1) {
	printf("writing %s to temp file failed.\r\n", contents);
	exit(1);
    }

    if (fseek(tmp, 0, SEEK_SET) != 0) {
	printf("seeking back to beginning of file failed for %s failed.\r\n",
	       contents);
    };

    return notepad_create(fd);
}
