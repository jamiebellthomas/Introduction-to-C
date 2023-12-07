CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3


extension: Extension/specific.h Extension/extension.c driver.c
	$(CC) driver.c Extension/extension.c -o extension $(PRODUCTION)

extension_s: driver.c extension.c specific.h
	$(CC) driver.c extension.c -o extension_s $(SANITIZE)

e_all: e_driverbsa_s e_driverbsa e_fibmemo e_sieve_s e_isfactorial # extfibmemo_s

e_driverbsa_s: bsa.h Extension/specific.h Extension/extension.c
	$(CC) driver.c Extension/extension.c -o driverbsa_s -I./Extension $(SANITIZE)

e_driverbsa: bsa.h Extension/specific.h Extension/extension.c
	$(CC) driver.c Extension/extension.c -o driverbsa -I./Extension $(PRODUCTION)

e_fibmemo: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o fibmemo -I./Extension $(PRODUCTION)

e_isfactorial: bsa.h Extension/specific.h Extension/extension.c isfactorial.c
	$(CC) isfactorial.c Extension/extension.c -o isfactorial -I./Extension $(PRODUCTION)

e_sieve_s: bsa.h Extension/specific.h Extension/extension.c sieve.c
	$(CC) sieve.c Extension/extension.c -o sieve_s -I./Extension $(PRODUCTION)

e_run: driverbsa driverbsa_s fibmemo sieve_s isfactorial # extfibmemo_s
	./e_driverbsa_s
	./e_isfactorial
	./e_fibmemo
	./e_sieve_s


