.PHONY: test clean bench

CC := gcc
CFLAGS := -Wall
SRCS := $(wildcard *.c)

test: $(SRCS)
	$(CC) -o $@ -O2 $^ $(CFLAGS)
	./test

clean: 
	@echo "Cleaning..."
	rm -f test

bench:
	g++ bench.cpp selection.c rand-select.c qsort-select.c -O2 -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o bench
	./bench