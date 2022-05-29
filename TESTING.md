# Testing

## Annie, Devon, Amanda

## Fuzz Testing

fuzz testing and possible output here

## Unit Testing

To unit test `create`, `make unitc`
To unit test `solve`, `make units`

`create` just creates a sudoku from an empty grid. It takes no arguments and returns `void`, so there's no need to do extensive unit testing for this
`solve` takes a few arguments that are worth checking: the array of arrays and a boolean that checks if a solution has already been found. We first solve a valid sudoku, then solve a sudoku that already has a solution found, and finally testing an invalid sudoku where a few numbers are > 9. See below for output.

Output:

```bash
$ make unitc
./unittestc
0 0 0 0 2 0 4 0 9 
3 0 7 4 5 6 0 0 0 
2 0 0 3 9 0 5 0 0 
4 5 8 2 3 0 0 9 7 
1 6 0 5 0 9 2 8 0 
7 0 0 8 6 4 0 0 1 
0 0 0 0 0 0 9 0 5 
0 0 5 6 0 0 0 1 0 
0 0 2 9 1 0 7 0 3 
PASS test create

PASS all test cases
```

```bash
$ make units
./unittests
Solved sudoku:
8 9 2 3 1 4 5 7 6 
5 7 3 2 8 6 4 1 9 
6 1 4 5 7 9 2 8 3 
3 5 9 1 6 2 7 4 8 
2 4 7 8 9 5 3 6 1 
1 6 8 4 3 7 9 2 5 
7 3 6 9 2 1 8 5 4 
9 2 5 6 4 8 1 3 7 
4 8 1 7 5 3 6 9 2 
PASS test sudokusolve0

PASS test sudokusolve1

Invalid grid. Values must be betwen 0-9 
PASS test sudokusolve2

PASS all test cases
```
