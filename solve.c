/*
 * solve.h - file that contains functions to solve a sudoku
 *
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "unittests.h"
#include "common.h"

/* see solve.h for description */
bool checkGrid(int (*arr)[9])
{
    // testing for bad values
    for (int x = 0; x < 9; x++)
    {
        for (int y = 0; y < 9; y++)
        {

            if (arr[y][x] < 0 || arr[y][x] > 9)
            {
                return false;
            }

            int temp = arr[y][x];

            if (temp == 0)
                continue;

            arr[y][x] = 0;
            if (!possible(arr, y, x, temp))
            {
                arr[y][x] = temp;
                return false;
            }
            arr[y][x] = temp;
        }
    }

    return true;
}

/* see solve.h for description */
void solve(int (*arr)[9], bool *printedOneSolution)
{
    // check if valid grid
    if (!checkGrid(arr))
    {
        fprintf(stderr, "Invalid grid. Values must be betwen 0-9 and follow sudoku rules. \n");
        return;
    }

    // check if there's already a solution printed for array
    if (*printedOneSolution)
    {
        return;
    }

    // loop through 2d array, trying numbers 1-9 on each cell and recursively calling solve again
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

/********************************************************
 **************** unit testing **************************
 ********************************************************/

#ifdef UNIT_TEST

// hard-coded sudoku puzzle
int test_sudokusolve0()
{
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
        {6, 0, 0, 8, 0, 0, 4, 7, 0}};

    bool printed = false;
    solve(a, &printed);

    END_TEST_CASE;
    return TEST_RESULT;
}

// try to solve where a solution was already printed
int test_sudokusolve1()
{
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
        {6, 0, 0, 8, 0, 0, 4, 7, 0}};

    bool printed = true;
    solve(a, &printed);

    END_TEST_CASE;
    return TEST_RESULT;
}

// input grid with values > 9
int test_sudokusolve2()
{
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
        {6, 0, 0, 8, 0, 0, 4, 7, 0}};

    bool printed = false;
    solve(a, &printed);

    END_TEST_CASE;
    return TEST_RESULT;
}

// input grid with invalid sudoku
int test_sudokusolve3()
{
    START_TEST_CASE("sudokusolve3");

    int a[9][9] = {
        {2, 0, 0, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    bool printed = false;
    solve(a, &printed);

    END_TEST_CASE;
    return TEST_RESULT;
}

int main(const int argc, const char *argv[])
{
    int failed = 0;

    failed += test_sudokusolve0();
    failed += test_sudokusolve1();
    failed += test_sudokusolve2();
    failed += test_sudokusolve3();

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
