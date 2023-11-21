CFLAGS := -Wall -Wextra -pedantic -std=c99 -Wvla -Wfloat-equal -Werror
SANI   := -g3 -fsanitize=address -fsanitize=undefined
CMP := gcc
part1: tr tr_s
	./tr
	./tr_s
	
tr: main1.c toprow.c
	$(CMP) main1.c toprow.c $(CFLAGS) -O3 -o tr

tr_s: main1.c toprow.c toprow.h
	$(CMP) main1.c toprow.c $(CFLAGS) $(SANI) -o tr_s

part2: sseq sseq_s
	./sseq
	./sseq_s

sseq: main2.c subseq.c subseq.h
	$(CMP) main2.c subseq.c $(CFLAGS) -O3 -o sseq

sseq_s: main2.c subseq.c
	$(CMP) main2.c subseq.c $(CFLAGS) $(SANI) -o sseq_s

all: part1 part2

clean: 
	rm -fr tr tr_s sseq sseq_s


