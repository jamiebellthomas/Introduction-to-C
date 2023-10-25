CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

anagrams: 5.1_anagrams.c
	$(CC) $(CFLAGS) 5.1_anagrams.c -o 5.1_anagrams.bin -lm

ansan: 5.1_anagrams.c
	gcc 5.1_anagrams.c -g3 -fsanitize=undefined -fsanitize=address -o ansan

clean:
	rm *.bin
