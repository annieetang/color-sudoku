LIBS = 
CFLAGS = -Wall -pedantic -std=c11 -g -ggdb 

.PHONY: all clean valgrind test

all: sudoku

sudoku:sudoku2.o $(LIBS)
	gcc $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f sudoku
	rm -f sudoku2.o

valgrind:
	make
	valgrind --leak-check=full --show-leak-kinds=all ./sudoku create | ./sudoku solve

test:
	make
	./sudoku create | ./sudoku solve