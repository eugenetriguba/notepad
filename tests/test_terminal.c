#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <cmocka.h>
#include <termios.h>
#include <stdio.h>

#include "../src/terminal.h"
#include "helpers.h"

void assert_equal_term_flags(struct termios t1, struct termios t2)
{
   assert_true(t1.c_oflag == t2.c_oflag);
   //assert_true(t1.c_lflag == t2.c_lflag);
   //assert_true(t1.c_cflag == t2.c_cflag);
   //assert_true(t1.c_iflag == t2.c_iflag);
   assert_true(t1.c_cc[VMIN] == t2.c_cc[VMIN]);
   assert_true(t1.c_cc[VTIME] == t2.c_cc[VTIME]);
}

// src/terminal.c: terminal_create
//
// The terminal_t from terminal_create() should
// have an original_settings member that has the
// termios settings of the current terminal.
void test_terminal_create_has_original_terminal_settings()
{
   terminal_t *term = create_test_notepad("q")->terminal;
   struct termios current_term;
   tcgetattr(term->file_descriptor, &current_term);

   assert_equal_term_flags(term->original_settings, current_term);
}

int main(void)
{
   const struct CMUnitTest tests[] = {
       cmocka_unit_test(test_terminal_create_has_original_terminal_settings)};

   return cmocka_run_group_tests(tests, NULL, NULL);
}
