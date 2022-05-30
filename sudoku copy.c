#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "unittest.h"

#define formatBool(b) ((b) ? "true" : "false")

#include <stdio.h>

/*
 * possible:
 * takes a 2d array and x and y coordinates for the grid and a number 1-9 as inputs
 * returns false if that number can't go in that coordinate point in the grid
 * because of the numbers in its row, column, or square. otherwise returns true
 */
bool possible(int (*arr)[9], int y, int x, int num);

/*
 * solve:
 * takes a 2d array, a random seed, and a generating bool as inputs
 * random seed is used so that the algorithm doesn't give solve the grid in the
 * same order every time, so that when a puzzle is generated it's random
 * if bool generating is true it removes a bunch of numbers before printing the
 * grid at the end
 * exits execution at the end of the function so that recursion stops solving other solutions
 */
void solve(int (*arr)[9], bool *printedOneSolution);

/*
 * printGrid:
 * loops through the 2d sudoku grid and prints the elements
 * in a grid with spaces in between
 */
void printGrid(int (*arr)[9]);

/*
 * generatePuzzle:
 * calls solve() on an empty sudoku grid
 * with generating set to true so that it removes a random amount of
 * numbers from the grid before printing out the grid
 */
void generatePuzzle();

void solutionCounter(int (*arr)[9], int *solutions);

void generatePuzzleHelper(int (*arr)[9], bool *created);

/* 
 * checkGrid: 
 * checks if the grid inputted to solve is valid 
 * integers are 0-9 and is a 9 by 9 grid
 */ 
bool checkGrid(int (*arr)[9]);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Wrong number of arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], "create") == 0)
    {
        srand(time(NULL));
        generatePuzzle();
        return 0;
    }
    if (strcmp(argv[1], "solve") == 0)
    {
        int a[9][9];
        for (int x = 0; x < 9; x++)
        {
            for (int y = 0; y < 9; y++)
            {
                if (scanf("%d ", &a[y][x]) != 1)
                {
                    scanf("%d ", &a[y][x]);
                }
            }
        }
        bool printed = false;
        solve(a, &printed);
        return 0;
    }

    fprintf(stderr, "incorrect format. do this: sudoku [solve|create]\n");
    return 2;
}

// static inline int min(const int a, const int b)
// {
//     return (a < b ? a : b);
// }

void printGrid(int (*arr)[9])
{
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            printf("%d ", arr[y][x]);
        }
        printf("\n");
    }
}

bool possible(int (*arr)[9], int y, int x, int num)
{
    for (int i = 0; i < 9; i++)
    {
        if (arr[y][i] == num)
            return false;
    }
    for (int i = 0; i < 9; i++)
    {
        if (arr[i][x] == num)
            return false;
    }
    int x0 = (int)(x / 3) * 3;
    int y0 = (int)(y / 3) * 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[y0 + i][x0 + j] == num)
                return false;
        }
    }
    return true;
}

/*
 * solutionCounter:
 * solves a given sudoku grid, and each time solved adds to
 * an int at a pointer passed in which keeps track of how many solutions there are
 * so that we can use this while creating a new puzzle that must have a unique solution
 * each recursive call only runs if there have been less than 2 solutions found
 */
void solutionCounter(int (*arr)[9], int *solutions)
{
    if (*solutions >= 2)
        return;
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            if (arr[y][x] == 0)
            {
                for (int n = 1; n < 10; n++)
                {
                    if (possible(arr, y, x, n))
                    {
                        arr[y][x] = n;
                        solutionCounter(arr, solutions);
                        arr[y][x] = 0;
                    }
                }
                return;
            }
        }
    }
    *solutions += 1;
}

void solve(int (*arr)[9], bool *printedOneSolution)
{  

    // check if valid grid
    if (!checkGrid(arr)) {
        fprintf(stderr, "Invalid grid. Values must be betwen 0-9 \n");
        return;
    }

    // check if there's already a solution printed for array
    if (*printedOneSolution) {
        return;
    }

    // loop through the array, perform backtracking and test possibe solutions
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            if (arr[y][x] == 0)
            {
                for (int n = 1; n < 10; n++)
                {
                    if (possible(arr, y, x, n))
                    {
                        arr[y][x] = n;
                        solve(arr, printedOneSolution);
                        arr[y][x] = 0;
                    }
                }
                return;
            }
        }
    }
    
    // set printed bool to true and print the grid
    *printedOneSolution = true;
    printGrid(arr);
}

/* 
 * checkGrid: 
 * 
 * checks if the grid inputted to solve is valid 
 * integers are 0-9 
 * don't need to check if the grid is 9x9 because the array will always be initialized to 9 by 9
 * any missing numbers will be autofilled with a 0 :)
 */ 
bool checkGrid(int (*arr)[9]) {

    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (arr[x][y] < 0 || arr[x][y] >= 9) {
                return false;
            }
        }
    }

    return true; 
}

/*
 * generatePuzzle:
 * creates an empty sudoku grid and places numbers in the 3 squares
 * diagonally from top left to bottom right. Then calls generatePuzzleHelper
 * on the grid, which solves it and takes numbers out.
 */
void generatePuzzle()
{
    int a[9][9];
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            a[y][x] = 0;
        }
    }

    // sets three diagonal squares of 9 numbers all to random numbers
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            while (true)
            {
                int trying = rand() % 9 + 1;
                if (possible(a, y, x, trying))
                {
                    a[y][x] = trying;
                    break;
                }
            }
        }
    }
    for (int x = 3; x < 6; x++)
    {
        for (int y = 3; y < 6; y++)
        {
            while (true)
            {
                int trying = rand() % 9 + 1;
                if (possible(a, y, x, trying))
                {
                    a[y][x] = trying;
                    break;
                }
            }
        }
    }
    for (int x = 6; x < 9; x++)
    {
        for (int y = 6; y < 9; y++)
        {
            while (true)
            {
                int trying = rand() % 9 + 1;
                if (possible(a, y, x, trying))
                {
                    a[y][x] = trying;
                    break;
                }
            }
        }
    }

    // printf("generated diagonal matrices:\n");
    // printGrid(a);

    bool createdPuzzle = false;
    generatePuzzleHelper(a, &createdPuzzle); // solves the puzzle, then removes a maximum of 54 numbers from it, then prints the puzzle!
}

void generatePuzzleHelper(int (*arr)[9], bool *created)
{
    if (*created)
        return;
    for (int y = 0; y < 9; y++)
    {
        for (int x = 0; x < 9; x++)
        {
            if (arr[y][x] == 0)
            {
                for (int n = 1; n < 10; n++)
                {
                    if (possible(arr, y, x, n))
                    {
                        arr[y][x] = n;
                        generatePuzzleHelper(arr, created);
                        arr[y][x] = 0;
                    }
                }
                return;
            }
        }
    }
    *created = true;
    // printf("Puzzle solved:\n");
    // printGrid(arr);
    int times = 0;
    int maxTimes = 40 + rand() % 15;
    while (times <= maxTimes)
    {
        // printf("Grid with %d numbers removed:\n", times);
        // printGrid(arr);
        // printf("\n");
        int x = rand() % 9;
        int y = rand() % 9;
        if (arr[y][x] == 0)
            continue;

        int temp = arr[y][x];
        arr[y][x] = 0;

        int b[9][9];
        for (int x0 = 0; x0 < 9; x0++)
        {
            for (int y0 = 0; y0 < 9; y0++)
            {
                b[y0][x0] = arr[y0][x0];
            }
        }

        int solutions = 0;
        solutionCounter(b, &solutions);
        // printf("solutions: %d\n", solutions);
        if (solutions != 1)
        {
            arr[y][x] = temp;
            continue;
        }
        times++;
    }
    printGrid(arr);
}

/********************************************************
 **************** unit testing **************************
 ********************************************************/

#ifdef UNIT_TEST

/* 
 * test_sudokucreate
 * 
 * creating/generating doesn't take any parameters and it initializes an 
 * empty array of arrays first, 
 * so no need to do extensive testing on it other than running it a few times
 * to see if any errors occur
 */
int test_sudokucreate() {
    START_TEST_CASE("create");
    generatePuzzle(); 
    END_TEST_CASE; 
    return TEST_RESULT; 
}

// hard-coded sudoku puzzle 
int test_sudokusolve0() {
    START_TEST_CASE("sudokusolve0");

    int a[9][9] = { 
        {8, 5, 6, 3, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 4, 0, 3, 0, 0},
        {0, 3, 4, 9, 0, 0, 6, 5, 1},
        {0, 0, 0, 1, 0, 0, 9, 0, 7},
        {0, 8, 0, 0, 0, 3, 2, 4, 0},
        {0, 0, 0, 0, 0, 7, 0, 0, 0},
        {5, 0, 0, 7, 0, 0, 8, 0, 0},
        {7, 1, 0, 4, 0, 2, 5, 3, 0},
        {6, 0, 0, 8, 0, 0, 4, 7, 0} 
    };

    bool printed = false; 
    solve(a, &printed); 

    END_TEST_CASE; 
    return TEST_RESULT; 
}

// try to solve where a solution was already printed 
int test_sudokusolve1() {
    START_TEST_CASE("sudokusolve1");

    int a[9][9] = { 
        {8, 5, 6, 3, 0, 0, 7, 0, 4},
        {0, 0, 0, 0, 4, 0, 3, 0, 0},
        {0, 3, 4, 9, 0, 0, 6, 5, 1},
        {0, 0, 0, 1, 0, 0, 9, 0, 7},
        {0, 8, 0, 0, 0, 3, 2, 4, 0},
        {0, 0, 0, 0, 0, 7, 0, 0, 0},
        {5, 0, 0, 7, 0, 0, 8, 0, 0},
        {7, 1, 0, 4, 0, 2, 5, 3, 0},
        {6, 0, 0, 8, 0, 0, 4, 7, 0} 
    };

    bool printed = true; 
    solve(a, &printed);

    END_TEST_CASE; 
    return TEST_RESULT; 
}

// input grid with values > 9
int test_sudokusolve2() {
    START_TEST_CASE("sudokusolve2");

    int a[9][9] = { 
        {8, 5, 6, 3, 0, 0, 799, 0, 4},
        {0, 0, 0, 0, 4, 0, 3, 0, 0},
        {0, 3, 43, 9, 0, 0, 6, 5, 1},
        {0, 0, 0, 1, 0, 0, 9, 0, 7},
        {0, 8, 0, 0, 0, 3, 2, 4, 0},
        {0, 0, 0, 0, 0, 7, 0, 0, 0},
        {5, 0, 0, 7, 0, 0, 8, 0, 0},
        {7, 1, 0, 4, 0, 288, 5, 3, 0},
        {6, 0, 0, 8, 0, 0, 4, 7, 0} 
    };

    bool printed = false; 
    solve(a, &printed); 

    END_TEST_CASE; 
    return TEST_RESULT; 
}

int main(const int argc, const char *argv[]) {
    int failed = 0; 

    failed += test_sudokucreate(); 

    failed += test_sudokusolve0(); 
    failed += test_sudokusolve1(); 
    failed += test_sudokusolve2();

    if (failed) {
        printf("FAIL %d test cases\n", failed);
        return failed; 
    }
    else {
        printf("PASS all test cases\n");
        return 0; 
    }
}

#endif // UNIT_TEST