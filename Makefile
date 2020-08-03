CC_FLAGS = -Wall -Wextra -pedantic

ENTRY_FILE = src/main.c
SRC_FILES = src/notepad.c src/terminal.c
TEST_FILES = tests/test_notepad.c tests/helpers.c

BUILD_OUTFILE = notepad
TEST_OUTFILE = test_run


build: $(ENTRY_FILE) $(SRC_FILES)
	$(CC) $(ENTRY_FILE) $(SRC_FILES) -o $(BUILD_OUTFILE) $(CC_FLAGS) -std=c11

test: $(TEST_FILES)
	$(CC) $(SRC_FILES) $(TEST_FILES) -l cmocka -o $(TEST_OUTFILE) $(CC_FLAGS) -std=gnu11
	./$(TEST_OUTFILE)

clean:
	rm -f $(BUILD_OUTFILE) $(TEST_OUTFILE)
