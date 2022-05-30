/*
 * create.h - file that contains functions to create a sudoku
 *
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "common.h"

/* see create.h for description */
void solutionCounter(int (*arr)[9], int *solutions)
{
    if (*solutions >= 2) // returns early if 2 or more solutions were already found
        return;
    for (int y = 0; y < 9; y++) // loops through 2d array, trying numbers 1-9 on each cell until all cells filled
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
    // out here means puzzle is solved.
    *solutions += 1; // increments value at pointer to solutions variable
}

/* see create.h for description */
void generatePuzzleHelper(int (*arr)[9], bool *created)
{
    if (*created)
        return;
    // goes through entire puzzle, trying each number 1-9 on each cell
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

    // out here, puzzle is solved. sets created to true to stop future
    // recursive calls from happening.
    *created = true;

    // sets up counter to keep track of how many numbers to remove
    // from solved puzzle and how many have been removed
    int times = 0;
    int maxTimes = 40 + rand() % 15;

    while (times <= maxTimes) // keep doing this until maxTimes numbers have been removed
    {
        // random x and y, if the number at that point is zero, don't do anything else
        int x = rand() % 9;
        int y = rand() % 9;
        if (arr[y][x] == 0)
            continue;

        // about to set number at x,y to zero, so stores the previous value in a temp int
        int temp = arr[y][x];
        arr[y][x] = 0;

        // copies arr to b so that solutionCounter, which alters the array,
        // can be used to count the number of solutions to arr without changing arr
        int b[9][9];
        for (int x0 = 0; x0 < 9; x0++)
        {
            for (int y0 = 0; y0 < 9; y0++)
            {
                b[y0][x0] = arr[y0][x0];
            }
        }

        // uses solutionCounter to determine how many solutions there are to the puzzle
        int solutions = 0;
        solutionCounter(b, &solutions);

        // if there isn't only 1 solution, set the number back to what it previously was and don't do anything else
        if (solutions != 1)
        {
            arr[y][x] = temp;
            continue;
        }
        times++; // if successfully removed a number, increment number of numbers removed
    }
    printGrid(arr); // prints grid to stdout
}

/* see create.h for description */
void generatePuzzle()
{
    // creates 9x9 2D array initially all numbers zero
    int a[9][9];
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {
            a[y][x] = 0;
        }
    }

    // sets all numbers in top left 3x3 square randomly
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
    // sets all numbers in middle 3x3 square randomly
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
    // sets all numbers in bottom right 3x3 square randomly
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

    // solves the puzzle and then takes numbers out
    bool createdPuzzle = false;
    generatePuzzleHelper(a, &createdPuzzle); // solves the puzzle, then removes a maximum of 54 numbers from it, then prints the puzzle!
}

/********************************************************
 **************** unit testing **************************
 ********************************************************/

#ifdef UNIT_TEST

#include "unittestc.h"
#include "common.h"

/*
 * test_sudokucreate
 *
 * creating/generating doesn't take any parameters and it initializes an
 * empty array of arrays first,
 * so no need to do extensive testing on it other than running it a few times
 * to see if any errors occur
 */
int test_sudokucreate()
{
    START_TEST_CASE("create");
    generatePuzzle();
    END_TEST_CASE;
    return TEST_RESULT;
}

int main(const int argc, const char *argv[])
{
    int failed = 0;

    failed += test_sudokucreate();

    if (failed)
    {
        printf("FAIL %d test cases\n", failed);
        return failed;
    }
    else
    {
        printf("PASS all test cases\n");
        return 0;
    }
}

#endif // UNIT_TEST
