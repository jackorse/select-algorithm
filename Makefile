.PHONY: test clean

CC := gcc
CFLAGS := -Wall
SRCS := $(wildcard *.c)

test: $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS)
	./test

clean: 
	@echo "Cleaning..."
	rm -f test
