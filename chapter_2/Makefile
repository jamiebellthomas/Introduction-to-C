CFLAGS := -Wall -Wextra -Wfloat-equal -Wvla -pedantic -std=c99
CC := /usr/bin/clang

secret: secret.c
	$(CC) $(CFLAGS) secret.c -o secret.bin

clean:
	rm *.bin
