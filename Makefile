CC_FLAGS = -Wall -Wextra -pedantic -std=c11

build: src/*.c
	$(CC) src/*.c -o notepad $(CC_FLAGS)

test:
	$(CC) tests/check_notepad.c -o check_notepad $(CC_FLAGS)
	$(CC) notepad.o check_notepad.o -l check -o check_notepad_tests
