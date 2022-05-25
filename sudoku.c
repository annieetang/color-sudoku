#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <time.h>

#define formatBool(b) ((b) ? "true" : "false")

#include <stdio.h>

/**
 * possible:
 * takes a 2d array and x and y coordinates for the grid and a number 1-9 as inputs
 * returns false if that number can't go in that coordinate point in the grid
 * because of the numbers in its row, column, or square. otherwise returns true
 */
bool possible(int (*arr)[9], int y, int x, int num);

/**
 * solve:
 * takes a 2d array, a random seed, and a generating bool as inputs
 * random seed is used so that the algorithm doesn't give solve the grid in the
 * same order every time, so that when a puzzle is generated it's random
 * if bool generating is true it removes a bunch of numbers before printing the
 * grid at the end
 * exits execution at the end of the function so that recursion stops solving other solutions
 */
void solve(int (*arr)[9], int seed, bool generating);

/**
 * printGrid:
 * loops through the 2d sudoku grid and prints the elements
 * in a grid with spaces in between
 */
void printGrid(int (*arr)[9]);

/**
 * generatePuzzle:
 * calls solve() on an empty sudoku grid
 * with generating set to true so that it removes a random amount of
 * numbers from the grid before printing out the grid
 */
void generatePuzzle();

void solutionCounter(int (*arr)[9], int *solutions);

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
        srand(time(NULL));
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
        solve(a, rand(), false);
        return 0;
    }

    fprintf(stderr, "incorrect format. do this: sudoku [solve|create]\n");
    return 2;
}

static inline int min(const int a, const int b)
{
    return (a < b ? a : b);
}

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

void solve(int (*arr)[9], int seed, bool generating)
{
    int start = seed % 9; // random num 1 to 9 start
    int y = start;
    do
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
                        solve(arr, seed, generating);
                        arr[y][x] = 0;
                    }
                }
                return;
            }
        }
        y = (y >= 8) ? 0 : y + 1;
    } while (y != start);

    if (generating)
    {
        int maxTimes = 40 + rand() % 24;
        for (int times = 0; times < maxTimes; times++)
        {
            int x = rand() % 9;
            int y = rand() % 9;
            if (arr[y][x] != 0)
            {
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
                printf("solutions: %d\n", solutions);
                if (solutions != 1)
                {
                    arr[y][x] = temp;
                    times--;
                }
                continue;
            }
            times--;
        }
    }
    printf("printing the thing\n");
    printGrid(arr);
}

/* old solve before I made it sus */
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

// check if puzzle is solvable and has unique solution 
//      use solve function to see if it has unique solution
//      keep count of how many solutions can be found
//      if count > 1 return false 
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
    int x = rand() % 9;
    int y = rand() % 9;
    int n = rand() % 9 + 1;
    a[y][x] = n;
    int random = rand();
    solve(a, random, true);
}