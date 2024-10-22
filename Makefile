.PHONY: clean

CC := gcc
G++ := g++
CFLAGS := -Wall -O3 -march=native 
BENCH_FLAGS := -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread
SRCS := $(wildcard *.c)
BENCH_SRCS := bench.cpp selection.c rand-select.c

test: $(SRCS)
	$(CC) -o $@ -g3 $^ $(CFLAGS)
	./$@

clean: 
	@echo "Cleaning..."
	rm -f test bench bench_manual out.json

bench: $(BENCH_SRCS)
	$(G++) -o $@ $^ $(CFLAGS) $(BENCH_FLAGS)
	./$@ --benchmark_out=out.json

bench-worst-random: $(BENCH_SRCS)
	$(G++) -o $@ $^ $(CFLAGS) $(BENCH_FLAGS) -DWORST_RANDOM
	./$@ --benchmark_out=out.json
