CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: parse # extfibmemo_s

parse: specific.h zero_one_parse.c
	$(CC) zero_one_parse.c -o parse $(PRODUCTION)

run: parse # extfibmemo_s
	./parse

clean:
	rm -f parse

