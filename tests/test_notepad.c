// clang-format off
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>
// Cmocka includes, must be in this order.
// clang-format on

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/notepad.h"
#include "../src/keys.h"
#include "helpers.h"

/**
 * src/notepad.c: startup_notepad_app
 *
 * Ensure that the startup_notepad_app's
 * return value is 0, since this is what
 * main() will use as it's exit code.
 */
void test_startup_notepad_app_return_value() {
    char contents[4];
    sprintf(contents, "%d", CTRL_KEY('q'));
    notepad_t *notepad = create_test_notepad(contents);

    assert_true(startup_notepad_app(notepad) == 0);
}

/**
 * src/notepad.c: read_all_from_fd
 *
 * Ensure that the contents in the file descriptor
 * are read into the notepad's contents, excluding
 * the quit 'q' command.
 */
void test_contents_in_notepad_include_fd_contents() {
    char *contents = "aaa";
    sprintf(contents, "%d", CTRL_KEY('q'));

    notepad_t *notepad = create_test_notepad(contents);

    read_all_from_fd(notepad);

    assert_string_equal(contents, notepad->contents);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_startup_notepad_app_return_value),
        cmocka_unit_test(test_contents_in_notepad_include_fd_contents)};

    return cmocka_run_group_tests(tests, NULL, NULL);
}
