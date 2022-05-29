# Makefile for 'sudoku' file 
# 
# Devon Starr, Annie Tang, Amanda Sun, CS50, Spring 2022

PROG = sudoku
OBJS = sudoku.o 
LIBS = 

CFLAGS = -Wall -pedantic -std=c11 -g -ggdb 
CC = gcc
MAKE = make 

$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

.PHONY: clean valgrind test

# sudoku:sudoku.o $(LIBS)
# 	gcc $(CFLAGS) -o $@ $^ -lm

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)

valgrind: $(PROG)
	valgrind --leak-check=full --show-leak-kinds=all ./sudoku create | ./sudoku solve
# valgrind --leak-check=full --show-leak-kinds=all ./sudoku create > output | ./sudoku solve < output

test: $(PROG)
	./sudoku create | ./sudoku solve