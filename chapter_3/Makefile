CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

microwave: 3.2_microwave.c
	$(CC) $(CFLAGS) 3.2_microwave.c -o 3.2_microwave.bin -lm

clean:
	rm *.bin
