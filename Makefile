.PHONY: test clean bench bench_manual

CC := gcc
CFLAGS := -Wall
SRCS := $(wildcard *.c)

test: $(SRCS)
	$(CC) -o $@ -O3 -march=native -g3 $^ $(CFLAGS)
	./test

clean: 
	@echo "Cleaning..."
	rm -f test

bench:
	g++ bench.cpp selection.c rand-select.c -O3 -march=native -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o bench
	./bench --benchmark_out=out.json
