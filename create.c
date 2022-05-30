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

/* see create.h for description */ 
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

/* see create.h for description */ 
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
int test_sudokucreate() {
    START_TEST_CASE("create");
    generatePuzzle(); 
    END_TEST_CASE; 
    return TEST_RESULT; 
}

int main(const int argc, const char *argv[]) {
    int failed = 0; 

    failed += test_sudokucreate(); 

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
