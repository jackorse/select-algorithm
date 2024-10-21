.PHONY: test clean bench

CC := gcc
CFLAGS := -Wall
SRCS := $(wildcard *.c)

test: $(SRCS)
	$(CC) -o $@ -O3 -msse4 -g3 $^ $(CFLAGS)
	./test

clean: 
	@echo "Cleaning..."
	rm -f test

bench:
	g++ bench.cpp selection.c rand-select.c qsort-select.c -O3 -msse4 -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o bench
	./bench --benchmark_out=out.json