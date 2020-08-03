#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include <termios.h>

#include "../src/terminal.h"
#include "helpers.h"


// src/terminal.c: terminal_create
//
// The terminal_t from terminal_create() should
// have an original_settings member that has the
// termios settings of the current terminal.
void test_terminal_create_has_original_terminal_settings() {
   terminal_t *term = create_test_notepad("")->terminal;
   struct termios current_term;

   tcgetattr(term->file_descriptor, &current_term);

   assert_true(term->original_settings.c_oflag == current_term.c_oflag);
}

int main(void) {
    const struct CMUnitTest tests[] = {
       cmocka_unit_test(test_terminal_create_has_original_terminal_settings)	
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
