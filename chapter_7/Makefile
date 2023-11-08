CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

maze: 7.1_maze.c
	$(CC) $(CFLAGS) 7.1_maze.c -o maze.bin -lm

mazesan: 7.1_maze.c
	gcc 7.1_maze.c -g3 -fsanitize=undefined -fsanitize=address -o mazesan

clean:
	rm *.bin
