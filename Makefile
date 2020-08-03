CC_FLAGS = -Wall -Wextra -pedantic -std=c11

build: src/*.c
	$(CC) src/*.c -o notepad $(CC_FLAGS)

test:
	$(CC) src/notepad.c  tests/*.c -l cmocka -o test_run -Wall -Wextra -pedantic
	./test_run

clean:
	rm -f notepad test_run
