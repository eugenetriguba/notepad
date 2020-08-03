#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/notepad.h"
#include "helpers.h"

void test_startup_notepad_app_return_value() {
    notepad_t *notepad = create_test_notepad("q");
    assert_true(startup_notepad_app(notepad) == 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_startup_notepad_app_return_value)
    };

    int count_fail_tests = cmocka_run_group_tests(tests, NULL, NULL);

    return (count_fail_tests == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
