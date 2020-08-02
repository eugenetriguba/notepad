#include <check.h>
#include <stdlib.h>

#include "../src/notepad.h"

START_TEST(test_startup_notepad_app_return_value) {
    int return_value;
    int fd = mkstemp("q");

    return_value = startup_notepad_app(notepad_create(fd));

    ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *notepad_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Notepad");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_startup_notepad_app_return_value);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int failed_tests = 0;
    Suite *s;
    SRunner *runner;

    s = notepad_suite();
    runner = srunner_create(s);

    srunner_run_all(runner, CK_NORMAL);
    failed_tests = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed_tests == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
