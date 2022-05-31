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

We anticipate the following modules or functions. They're contained in separate files for the purpose of unit testing:

*main*, which parses arguments and either creates or solves a puzzle depending on the first argument. Found in `sudoku.c`
*generatePuzzle*, which creates a valid sudoku puzzle with more than 40 missing numbers. Found in `create.c`
*printGrid*, which loops through a 2d array of ints and prints them in a grid to stdout. Found in `common.c`
*possible*, which returns true if a number specified is a possible solution in the grid cell specified. Found in `common.c`
*solve*, which takes in a 2d array (a puzzle) and prints to stdout the solved puzzle. Found in `solve.c`

### Pseudo code for logic/algorithmic flow

We anticipate the following modules or functions:

1. execute from a command line as shown in the User Interface
2. parse the command line, validate parameters and checks the number of argumentes
3. if first argument is “create”, call `generatePuzzle` from the `create.c` file.
	1. `generatePuzzle` creates ane mpty sudoku grid and places numbers in the 3 square diagonally from top left to bottom right.
		1. It creates a 9x9 2D array as initially all 0s
		2. It will then set all numbers in the top left 3x3 square randomly
		3. Then it will set all numbers in the middle 3x3 square randomly
		4. Then it sets all numbers in the bottom right 3x3 square randomly
	2. It will then call `generatePuzzleHelper` on the grid it created to solve and remove a random number of numbers from the grid so the user can have fun solving it.
		1. It goes through the entire puzzle grid, trying each number 1-9 on each cell.
	3. The helper calls a `possible` function that helps check if the value inputted is a "possible" value (aka it's a valid number in that grid). This is in the `common.c` directory as it will be used by both the `create` and `solve` files for the sudoku.
		1. `possible` takes a 2D array and the current number and its "coordinate" points to check.
		2. It will first check the rows to make sure the number is possible in the row 
		3. Then it will check the column to make sure the number is possible in the solumn.
		4. Then it checks each 3x3 square to make sure its possible there and returns a boolean if it's successful or not.
4. if the argument is "solve", call `solve` from the `solve.c` file.
	1. But before that, it will create a 2D array by reading a predetermined format from stdin (must be an int + space + int + space, etc. 9x9)
	2. Then, it will pass this array to the `solve` function.
		1. Solve will first check if the grid is valid by calling `checkGrid` helper function.
			1. This will test for any "bad" values in the 9x9 grid by returning false if any value is not an integer 1-9.
		2. Then, it will check if there is a solution already printed for the array. This is determined by a boolean parameter passed in, and it exists because some sudokus generated can potentially have more than one solution, so it's just checking and only solving grids that haven't been tried yet.
		3. Then, we will loop through the 2D array and try numbers 1-9 on each cell and recursively call `solve` again to iterate through all possible values and solutions.
		4. If everything works out well, we will `printGrid` and set the boolean for printOneSolution to `true`, since it successfully printed one solution.

The sudoku completes and exits when it has finished solving and printing out the resulting sudoku puzzle.

### Dataflow through modules

1. *main* parses parameters and goes to either *generatePuzzle* or *solve* that will create the 2D array
2. *generatePuzzle* is stored in `create.h` where it will create an empty 2D array to hold the sudoku grid, place numbers in the 3 squares diagonally from top left to bottom right,a dn then it will call a helper function `generatePuzzleHelper` on that 2D array grid to solve and remote numbers to make a grid for users to solve.
	1. *generatePuzzle* will then call *printGrid*, a function in `common.h` that will take the 2D array grid and print it out by looping through it.
3. *solve* will call the `possible` function from `common.h` to check if a value inputted into a grid will make the sudoku solvable. If it doesn't, it will backtrack and test another solution until one is found. Possible takes the 2D array to check as a parameter.
	1. After this, *solve* will then call *printGrid*, the same one *generatePuzzle* uses, and take the 2D array and prints it to the console for the user to see the solution.

### Major data structures

* A 2D array to hold the 9x9 sudoku grid

### Testing plan

*Unit testing*. A small test program to test each module to make sure it does what it's supposed to do. Modules: creating the sudoku, solving the sudoku.

*Fuzz testing*. Use the creator to generate **n** puzzles, where **n** is a command-line argument and test solver for these grids. Check the following:
	- The solution is valid, i.e, it follows Sudoku rules and doesn’t change already filled cells in the grids
	- The solver checks if each given puzzle has a unique solution (so you are also testing your creator n times).
