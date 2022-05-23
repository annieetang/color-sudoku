# Sudoku Design File

## CS 50 22S, Final Project

## Members: Devon Starr, Amanda Sun, Annie Tang

This Design Spec contains several sections:

* User interface
* Inputs and Outputs
* Functional decomposition into modules
* Pseudo code for logic/algorithmic flow
* Dataflow through modules
* Major data structures
* Testing plan

### User interface

The sudoku will generate a sudoku grid with at least 40 missing numbers. The sudoku has two main parts: creating and solving the sudoku.

The sudoku’s only interface with the user is on the command-line; it has one argument: `create` or `solve`.

It can be run as follows:

```bash
./sudoku create
./sudoku solve
```

### Inputs and outputs

Input: the only inputs are command-line parameters; see the User Interface above.

Output: If `create`, a randomized sudoku puzzle with at least 40 missing numbers. If `solve`, a solved version of the sudoku puzzle from the `create` output. It will be a puzzle that has a unique solution and `solve` must not change any given numbers in the puzzle.

### Functional decomposition into modules

We anticipate the following modules or functions:

*main*, which parses arguments and either creates or solves a puzzle depending on the first argument.
*generatePuzzle*, which creates a valid sudoku puzzle with more than 40 missing numbers.
*printGrid*, which loops through a 2d array of ints and prints them in a grid to stdout
*possible*, which returns true if a number specified is a possible solution in the grid cell specified.
*solve*, which takes in a 2d array (a puzzle) and prints to stdout the solved puzzle.

### Pseudo code for logic/algorithmic flow

We anticipate the following modules or functions: (more about algorithm)

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters
3. if first argument is “create”,
	1. Solves an empty sudoku puzzle
	2. takes some numbers out
	3. returns unsolved puzzle
4. If first argument is “solve”,
	1. reads 2d array of ints from stdin,
	2. solves puzzle,
	3. prints solved puzzle to stdout

The sudoku completes and exits when it has finished solving and printing out the resulting sudoku puzzle.

### Dataflow through modules (modulate codes for solve/create possibly)

how array used in each part of algorithm

1. *main* parses parameters and goes to either *generatePuzzle* or *solve*
2. *generatePuzzle* and then *printGrid*
3. *solve* uses possible and then *printGrid*

### Major data structures

* A 2D array to hold the 9x9 sudoku grid

### Testing plan

*Unit testing*. A small test program to test each module to make sure it does what it's supposed to do. Modules: creating the sudoku, solving the sudoku.

*Fuzz testing*. Use the creator to generate **n** puzzles, where **n** is a command-line argument and test solver for these grids. Check the following:
	- The solution is valid, i.e, it follows Sudoku rules and doesn’t change already filled cells in the grids
	- The solver checks if each given puzzle has a unique solution (so you are also testing your creator n times).
