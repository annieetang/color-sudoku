# Implementation

## Detailed pseudo code for each of the functions

`int main(int argc, char const *argv[])`

```
returns nonzero and prints error if the the wrong number of command-line arguments are given
if first and only argument is "create",
    sets up random number system using the current time
    generates a puzzle using generatePuzzle()
    returns 0
if first and only argument is "solve",
    creates a 9x9 2d array to store the puzzle
    for each x value 0 to 8 in the grid,
        for each y value 0 to 8 in the grid,
            attempts to scan an integer from stdin and if fails,
                tries to scan another integer from stdin
    creates a bool initially set to false
    solves puzzle, using the address of the bool to keep track of how many solutions have been printed
    returns 0
returns nonzero and prints error for incorrect arguments
```

## Pseudocode used in both `./sudoku create` and `./sudoku solve`

`bool possible(int (*arr)[9], int y, int x, int num)`

```
for each array index in the row at x,y
    if the array element at the given y value and the row index is equal to the number specified,
        return false
for each array index in the column at x,y
    if the array element at the given x value and the column index is equal to the number specified,
        return false
creates ints x0 and y0 which are x and y rounded down to the nearest multiple of 3
for i 0 to 2
    for j 0 to 2
        if the array element at (x0 + j, y0 + i) is equal to the number specified,
            return false
return true
```

## Pseudocode for functions only used for `./sudoku create`

`void solutionCounter(int (*arr)[9], int *solutions)`

```
if value at solutions pointer is at least 2,
    return early

for y 0 to 8
    for x 0 to 8
        if the array element at x,y is 0,
            for n 1 to 9
                if n is possible at the current point x,y in the array,
                    sets the array element at x,y to n
                    runs solutionCounter again
                    sets array element at x,y back to 0
            return early
adds 1 to value at solutions pointer
```

`void generatePuzzle()`

```
creates empty sudoku array
sets all elements in 2d array to zero
for each point x,y in the top-left 3x3 square in the array
    while true,
        generates random number 1 to 9
        if the number is possible at x,y,
            insert it
            break out of while loop
for each point x,y in the middle 3x3 square in the array
    while true,
        generates random number 1 to 9
        if the number is possible at x,y,
            insert it
            break out of while loop
for each point x,y in the bottom-right 3x3 square in the array
    while true,
        generates random number 1 to 9
        if the number is possible at x,y,
            insert it
            break out of while loop
creates a bool initially set to false
uses generatePuzzleHelper to solve the puzzle and then remove values from it, passing in the address to the bool
```

`void generatePuzzleHelper(int (*arr)[9], bool *created)`

```
if value at bool pointer given is true,
    returns early
for y 0 to 8
    for x 0 to 8
        if the array element at x,y is 0,
            for n 1 to 9
                if n is possible at the current point x,y in the array,
                    sets the array element at x,y to n
                    runs generatePuzzleSolver again
                    sets array element at x,y back to 0
            return early
sets value at created equal to true
creates an int "times" initially zero to represent amount of numbers removed
creates an int maxTimes between 40 and 54 to represent amount of numbers to remove
while times is less than or equal to maxTimes,
    creates two random x and y ints 1 to 9
    if the array element at x,y is 0
        continue; don't do anything else
    creates temp int to store the current value in the array at x,y
    sets array value at x,y to 0
    makes a copy of the current array
    uses solutionCounter to count number of solutions in the copy
    if the number of solutions is not 1,
        sets the array value at x,y back to the temp value it was before set to 0
        continue; don't do anything else
    increment times
print the 2d sudoku array
```

## Pseudocode for function used in `./sudoku solve`

`void solve(int (*arr)[9], bool *printedOneSolution)`

```
if value at printedOneSolution pointer is true,
    return early

for y 0 to 8
    for x 0 to 8
        if the array element at x,y is 0,
            for n 1 to 9
                if n is possible at the current point x,y in the array,
                    sets the array element at x,y to n
                    runs solve again
                    sets array element at x,y back to 0
            return early
sets value at printedOneSolution equal to true
prints solved sudoku grid
```

## Detailed APIs used

### from `stdlib.h`

```c
/**************** rand ****************/
/*
 * returns the next pseudo-random number in the series. The range value of the 
 * number series is between 0 and RAND_MAX. RAND_MAX is a macro defined in stdlib.h 
 * header file, whose value is the maximum value, which can return by rand() function. 
 * The value of RAND_MAX is greater but not less than 32767 depending on the C libraries
 */
int rand();

/**************** srand ****************/
/*
 * seeds the random number generator used by the function rand.
 */
void srand(unsigned int seed);
```

### from `time.h`

```c
/**************** time ****************/
/*
 * returns the time since 00:00:00 UTC, January 1, 1970 (Unix timestamp) in seconds. 
 * If second is not a null pointer, the returned value is also stored in the object 
 * pointed to by second. Used for our purposes to seed the random number generator based
 * on the current time so that each time program runs it generates different numbers
 */
time_t time( time_t *second );
```

## Data structures

the only data structure used in *sudoku.c* is an `int[9][9]` to represent the sudoku puzzle.

when `./sudoku create` is run it creates an `int[9][9]` initially filled with zeros, solves it, and removes some numbers.

when `./sudoku solve` is run, 81 numbers are read in from stdin and stored into an `int[9][9]` and it is then solved and printed.
