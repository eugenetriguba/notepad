CC_FLAGS = -Wall -Wextra -pedantic
ENTRY_FILE = src/main.c
SRC_FILES = src/notepad.c src/terminal.c
TEST_FILES = tests/test_notepad.c tests/helpers.c

build: $(ENTRY_FILE) $(SRC_FILES)
	$(CC) $(ENTRY_FILE) $(SRC_FILES) -o notepad $(CC_FLAGS) -std=c11

test: $(TEST_FILES)
	$(CC) $(SRC_FILES) $(TEST_FILES) -l cmocka -o test_run $(CC_FLAGS) -std=gnu11
	./test_run

clean:
	rm -f notepad test_run
