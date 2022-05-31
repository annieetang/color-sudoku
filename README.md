# Sudoku

## CS 50 22S, Final Project

## Members: Devon Starr, Amanda Sun, Annie Tang

### Usage

`sudoku` must be called with `make` and then `./sudoku [create|solve]`.

To clean up files, run `make clean`

See `TESTING.md` for information about tests and how to run them.

### Assumptions

For solver:

* Sudoku grid is inputted in the correct format - 9 rows of 9 integers separated by spaces, as seen in `testfiles/input1.txt`, for example.

### Files

* `.gitignore` - ignores files
* `DESIGN.md`- general plan for project including UI, IO, functions, modules, pseudo code, and data structures
* `IMPLEMENTATION.md` - specific, hardware and language-type implementation of design
* `Makefile`- see Usage
* `README.md`- this file
* `common.c` & `common.c`- functions used by more than one of `sudoku.c`, `solve.c`, and `create.c`
* `create.c` * `create.h` - functions for creating a sudoku puzzle
* `solve.c` * `solve.h` - functions for solving a sudoku puzzle
* `testing.sh`- fuzz testing and some specific test cases for solver
* `unittests.h` & `unittestc.h` - header files used for unit testing
* `testfiles/input*.txt` - text files that store unsolved sudoku puzzled, used to test solver
* `testfiles/answer*.txt` - text files that store sudoku solutions, used to test solver

### Extra Credit Files

#### In `/colorsudoku/src`:

* `App.js` - includes all of the html elements for displaying the app, and also all of the javascript for functionality. javascript functions were adapted from our `sudoku.c`, `solve.c`, and `create.c`.
* `App.css` - all styling for elements in our react app
* all other files in `/colorsudoku` were auto generated and not edited by our team

## Extra Credit!

For extra credit our team made a react app where you can play sudoku, but with *colors*!

### To run colorsudoku locally

* make sure `node.js` is installed
    * to check if you have `node`, in terminal type `node -v`
    * if no version exists, `brew install node` for mac users or just download it from the internet for windows users
* cd into `colorsudoku` folder
* run `npm install` to install the `/node_modules` folder
* run `npm start` to host the app locally in your browser!

## Color sudoku hosted website -----> https://colorsudoku.netlify.app/
