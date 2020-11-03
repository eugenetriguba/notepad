OPTIMIZATION_FLAG = -O0
CC_FLAGS = -Wall -Wextra -pedantic $(OPTIMIZATION_FLAG)

SRC_ENTRY_FILE = src/main.c
SRC_FILES = src/notepad.c src/terminal.c src/utils.c

TEST_FILES = tests/test_notepad.c tests/test_terminal.c
TEST_HELPERS = tests/helpers.c

BUILD_OUTFILE = np
TEST_OUTFILE = test_run


build: $(SRC_ENTRY_FILE) $(SRC_FILES)
	$(CC) $(SRC_ENTRY_FILE) $(SRC_FILES) -o $(BUILD_OUTFILE) $(CC_FLAGS) -std=c11

build_optimized: $(SRC_ENTRY_FILE) $(SRC_FILES)
	$(MAKE) OPTIMIZATION_FLAG=-O3 build

memcheck:
	$(MAKE) build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./np

test: $(TEST_FILES) $(TEST_HELPERS)
	@for file in $(TEST_FILES); do \
	    $(CC) $(SRC_FILES) $${file} $(TEST_HELPERS) -l cmocka -o $(TEST_OUTFILE) $(CC_FLAGS) -std=gnu11; \
	    echo "Running $${file}"; \
	    ./$(TEST_OUTFILE); \
	    echo -e "\n"; \
	done

clean:
	rm -f $(BUILD_OUTFILE) $(TEST_OUTFILE) ./*.gcno ./*.gcda

