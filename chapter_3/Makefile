CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

microwave: 3.2_microwave.c
	$(CC) $(CFLAGS) 3.2_microwave.c -o 3.2_microwave.bin -lm

music: 3.3_music.c
	$(CC) $(CFLAGS) 3.3_music.c -o 3.3_music.bin -lm

clean:
	rm *.bin
