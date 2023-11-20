CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

anagrams1: anagrams1.c
	$(CC) $(CFLAGS) anagrams1.c -o anagrams1 -lm

anagrams2: anagrams2.c
	$(CC) $(CFLAGS) anagrams2.c -o anagrams2 -lm

isograms1: isograms1.c
	$(CC) $(CFLAGS) isograms1.c -o isograms1 -lm

isograms2: isograms2.c
	$(CC) $(CFLAGS) isograms2.c -o isograms2 -lm

mutating1: mutating1.c
	$(CC) $(CFLAGS) mutating1.c -o mutating1 -lm

mutating2: mutating2.c
	$(CC) $(CFLAGS) mutating2.c -o mutating2 -lm

ansan1: anagrams1.c
	gcc anagrams1.c -g3 -fsanitize=undefined -fsanitize=address -o ansan1

clean:
	rm *.bin
