#include "helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../src/notepad.h"

notepad_t *create_test_notepad(char *contents)
{
    FILE *tmp = tmpfile();
    int fd = fileno(tmp);
    size_t num_of_elements = strlen(contents) + 1;

    if (fwrite(contents, sizeof(char), num_of_elements, tmp) != num_of_elements)
    {
        printf("writing %s to temp file failed.\r\n", contents);
        exit(EXIT_FAILURE);
    }

    if (fseek(tmp, 0, SEEK_SET) != 0)
    {
        printf("seeking back to beginning of file failed for %s failed.\r\n",
               contents);
        exit(EXIT_FAILURE);
    };

    return notepad_create(fd);
}
