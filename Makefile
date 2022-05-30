# Makefile for 'sudoku' file 
# 
# Devon Starr, Annie Tang, Amanda Sun, CS50, Spring 2022

PROGS = sudoku
OBJS = common.o create.o solve.o sudoku.o 
LIBS = 

CFLAGS = -Wall -pedantic -std=c11 -g -ggdb 
CC = gcc
MAKE = make 

.PHONY: all clean valgrind unitc units test 

all: sudoku

$(PROGS): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

common.o: common.h 
create.o: create.h unittestc.h common.h 
solve.o: solve.h unittests.h common.h

unittestc: create.c common.c
	$(CC) $(CFLAGS) -DUNIT_TEST create.c common.c -o $@

unittests: solve.c common.c 
	$(CC) $(CFLAGS) -DUNIT_TEST solve.c common.c -o $@ 

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROGS)
	rm -f unittestc
	rm -f unittests

valgrind: $(PROGS)
	valgrind --leak-check=full --show-leak-kinds=all ./sudoku create | ./sudoku solve

unitc: unittestc
	./unittestc

units: unittests
	./unittests

test: $(PROGS)
	./testing.sh
