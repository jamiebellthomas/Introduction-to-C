CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

microwave: 3.2_microwave.c
	$(CC) $(CFLAGS) 3.2_microwave.c -o 3.2_microwave.bin -lm

music: 3.3_music.c
	$(CC) $(CFLAGS) 3.3_music.c -o 3.3_music.bin -lm

yahtzee: 3.4_yahtzee.c
	$(CC) $(CFLAGS) 3.4_yahtzee.c -o 3.4_yahtzee.bin -lm

110: 3.5_110.c
	$(CC) $(CFLAGS) 3.5_110.c -o 3.5_110.bin -lm

test: test.c
	$(CC) $(CFLAGS) test.c -o test.bin -lm

1102: 3.5_110_2.c
	$(CC) $(CFLAGS) 3.5_110_2.c -o 3.5_110_2.bin -lm

clean:
	rm *.bin
