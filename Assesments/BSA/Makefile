CC=clang
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 -Werror
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3

all: driverbsa_s driverbsa fibmemo sieve_s isfactorial # extfibmemo_s

driverbsa_s: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa_s -I./Alloc $(SANITIZE)

driverbsa: bsa.h Alloc/specific.h Alloc/alloc.c driver.c
	$(CC) driver.c Alloc/alloc.c -o driverbsa -I./Alloc $(PRODUCTION)

fibmemo: bsa.h Alloc/specific.h Alloc/alloc.c fibmemo.c
	$(CC) fibmemo.c Alloc/alloc.c -o fibmemo -I./Alloc $(PRODUCTION)

isfactorial: bsa.h Alloc/specific.h Alloc/alloc.c isfactorial.c
	$(CC) isfactorial.c Alloc/alloc.c -o isfactorial -I./Alloc $(PRODUCTION)

sieve_s: bsa.h Alloc/specific.h Alloc/alloc.c sieve.c
	$(CC) sieve.c Alloc/alloc.c -o sieve_s -I./Alloc $(PRODUCTION)

## Only if you do an extension. Uncomment in all, extfibmemo_s and run.
extfibmemo_s: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o extfibmemo_s -I./Extension $(SANITIZE)

run: driverbsa driverbsa_s fibmemo sieve_s isfactorial # extfibmemo_s
	./driverbsa_s
	./isfactorial
	./fibmemo
	./sieve_s
	#./extfibmemo_s

clean:
	rm -f driverbsa_s driverbsa fibmemo extfibmemo_s isfactorial sieve_s

extension: bsa.h Extension/specific.h Extension/extension.c driver.c
	$(CC) driver.c Extension/extension.c -o extension $(PRODUCTION)

extension_s: bsa.h driver.c Extension/specific.h Extension/extension.c
	$(CC) driver.c extension.c -o extension_s $(SANITIZE)

e_all: e_driverbsa_s e_driverbsa e_fibmemo e_sieve_s e_isfactorial # extfibmemo_s

e_driverbsa_s: bsa.h Extension/specific.h Extension/extension.c
	$(CC) driver.c Extension/extension.c -o e_driverbsa_s -I./Extension $(SANITIZE)

e_driverbsa: bsa.h Extension/specific.h Extension/extension.c
	$(CC) driver.c Extension/extension.c -o e_driverbsa -I./Extension $(PRODUCTION)

e_fibmemo: bsa.h Extension/specific.h Extension/extension.c fibmemo.c
	$(CC) fibmemo.c Extension/extension.c -o e_fibmemo -I./Extension $(PRODUCTION)

e_isfactorial: bsa.h Extension/specific.h Extension/extension.c isfactorial.c
	$(CC) isfactorial.c Extension/extension.c -o e_isfactorial -I./Extension $(PRODUCTION)

e_sieve_s: bsa.h Extension/specific.h Extension/extension.c sieve.c
	$(CC) sieve.c Extension/extension.c -o e_sieve_s -I./Extension $(PRODUCTION)

e_run: e_fibmemo e_sieve_s e_isfactorial # extfibmemo_s
	./e_isfactorial
	./e_fibmemo
	./e_sieve_s