# Testing

## Annie, Devon, Amanda

## Fuzz Testing

To fuzz test `sudoku`, `make test`. This calls the `testing.sh` shell script.
When run, `testing.sh` asks for a number `n` of puzzles to create and solve, and then creates and solves `n` puzzles and prints out each unsolved and solved version.

During the fuzz test, when a puzzle is created, it means that it only has one solution because our creator (see create.c) only prints out the puzzle if there is only one possible solution.

When a puzzle is solved, it means that it follows all sudoku rules and that no already filled cells are changed because our solver (see solve.c) only puts in numbers where the number is zero (meaning it was not already filled) and it is possible for that number to go there according to the sudoku rules.

Also included in `testing.sh` are a few hard-coded sudoku tests, where a puzzle and its solution are both already stored in a file `answer*.txt`, and an error is printed if the solver's solution doesn't match the correct solution stored in `answer*.txt`. If no errors are printed, this means all tests passed.

Output:

```bash
$ make test
./testing.sh

******************* sudoku tester *******************
***generating and solving 10 sudokus using ./sudoku create | ./sudoku solve***
***  delaying one second each time to refresh the random number generator  ***
Enter number of iterations: 
5
Creating sudoku 1...
0 0 1 3 2 0 0 0 4 
5 9 0 0 0 0 8 0 2 
0 0 0 0 0 0 1 0 0 
0 0 9 0 5 0 0 0 8 
3 8 0 2 0 0 0 0 1 
0 0 7 0 0 8 9 4 0 
0 2 4 0 0 0 6 0 9 
0 0 0 9 1 2 0 0 7 
0 0 0 6 0 0 0 5 0 

Solving sudoku 1...
8 6 1 3 2 5 7 9 4 
5 9 3 4 7 1 8 6 2 
4 7 2 8 6 9 1 3 5 
1 4 9 7 5 6 3 2 8 
3 8 6 2 9 4 5 7 1 
2 5 7 1 3 8 9 4 6 
7 2 4 5 8 3 6 1 9 
6 3 5 9 1 2 4 8 7 
9 1 8 6 4 7 2 5 3 

Creating sudoku 2...
1 5 0 0 0 6 0 8 0 
3 0 0 0 7 0 0 6 4 
0 0 0 0 0 0 0 1 0 
0 0 4 0 0 0 0 0 0 
5 9 8 0 0 0 0 0 3 
0 0 3 8 0 0 0 0 2 
0 0 0 6 0 4 0 0 0 
0 2 0 7 3 0 4 0 0 
9 0 5 2 0 0 0 3 7 

Solving sudoku 2...
1 5 2 3 4 6 7 8 9 
3 8 9 1 7 5 2 6 4 
4 6 7 9 2 8 3 1 5 
2 7 4 5 1 3 8 9 6 
5 9 8 4 6 2 1 7 3 
6 1 3 8 9 7 5 4 2 
7 3 1 6 5 4 9 2 8 
8 2 6 7 3 9 4 5 1 
9 4 5 2 8 1 6 3 7 

Creating sudoku 3...
0 6 0 1 9 0 0 3 0 
4 0 0 3 8 0 6 0 0 
7 0 0 0 0 5 4 0 0 
1 0 0 0 0 8 0 0 5 
0 0 9 0 0 3 2 0 0 
3 0 0 0 5 9 1 6 4 
8 0 3 0 0 2 0 7 6 
0 5 0 9 0 1 0 0 0 
0 0 0 0 3 0 5 0 0 

Solving sudoku 3...
2 6 5 1 9 4 7 3 8 
4 9 1 3 8 7 6 5 2 
7 3 8 2 6 5 4 1 9 
1 7 6 4 2 8 3 9 5 
5 4 9 6 1 3 2 8 7 
3 8 2 7 5 9 1 6 4 
8 1 3 5 4 2 9 7 6 
6 5 4 9 7 1 8 2 3 
9 2 7 8 3 6 5 4 1 

Creating sudoku 4...
0 4 9 1 0 0 0 0 3 
5 1 0 0 0 8 0 6 4 
0 0 8 0 0 0 5 2 1 
0 7 0 9 0 3 6 0 0 
0 0 5 6 1 7 0 0 9 
6 0 0 0 2 0 1 0 7 
7 0 4 0 6 0 8 0 0 
8 5 0 0 0 0 0 7 6 
0 2 6 7 8 4 0 0 0 

Solving sudoku 4...
2 4 9 1 5 6 7 8 3 
5 1 7 2 3 8 9 6 4 
3 6 8 4 7 9 5 2 1 
1 7 2 9 4 3 6 5 8 
4 8 5 6 1 7 2 3 9 
6 9 3 8 2 5 1 4 7 
7 3 4 5 6 1 8 9 2 
8 5 1 3 9 2 4 7 6 
9 2 6 7 8 4 3 1 5 

Creating sudoku 5...
0 0 0 0 0 3 6 7 5 
0 0 0 0 7 0 0 0 0 
2 0 0 9 5 0 4 0 0 
1 0 7 8 0 0 0 4 6 
0 0 0 0 0 0 0 0 0 
0 3 0 7 0 6 5 0 1 
0 4 0 0 0 0 0 0 7 
0 5 2 0 8 1 0 0 0 
9 0 0 5 0 0 0 0 0 

Solving sudoku 5...
8 9 4 2 1 3 6 7 5 
3 1 5 6 7 4 2 9 8 
2 7 6 9 5 8 4 1 3 
1 2 7 8 3 5 9 4 6 
5 6 8 1 4 9 7 3 2 
4 3 9 7 2 6 5 8 1 
6 4 1 3 9 2 8 5 7 
7 5 2 4 8 1 3 6 9 
9 8 3 5 6 7 1 2 4 

******************* hardcoded sudoku tester, only prints if failed *******************
```

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
