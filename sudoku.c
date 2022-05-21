#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define formatBool(b) ((b) ? "true" : "false")
#include <math.h>
#include <ctype.h>
#include <time.h>

#include <stdio.h>

bool possible(int (*arr)[9], int y, int x, int num);
void solve(int (*arr)[9], int seed, bool generating);
void printGrid(int (*arr)[9]);
void generatePuzzle();

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
        // int a[9][9] = {
        //     {5, 3, 0, 0, 7, 0, 0, 0, 0},
        //     {6, 0, 0, 1, 9, 5, 0, 0, 0},
        //     {0, 9, 8, 0, 0, 0, 0, 6, 0},
        //     {8, 0, 0, 0, 6, 0, 0, 0, 3},
        //     {4, 0, 0, 8, 0, 3, 0, 0, 1},
        //     {7, 0, 0, 0, 2, 0, 0, 0, 6},
        //     {0, 6, 0, 0, 0, 0, 2, 8, 0},
        //     {0, 0, 0, 4, 1, 9, 0, 0, 5},
        //     {0, 0, 0, 0, 8, 0, 0, 7, 9}};
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
        printf("=================\n");
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
        int maxTimes = 40 + rand() % 20;
        // printf("maxTimes: %d\n", maxTimes);
        for (int times = 0; times < maxTimes; times++)
        {
            int x = rand() % 9;
            int y = rand() % 9;
            if (arr[y][x] != 0)
            {
                arr[y][x] = 0;
                continue;
            }
            times--;
        }
    }
    printGrid(arr);
    exit(0);
}
// void solve(int (*arr)[9])
// {
//     for (int y = 0; y < 9; y++)
//     {
//         for (int x = 0; x < 9; x++)
//         {
//             if (arr[y][x] == 0)
//             {
//                 for (int n = 1; n < 10; n++)
//                 {
//                     if (possible(arr, y, x, n))
//                     {
//                         arr[y][x] = n;
//                         solve(arr);
//                         arr[y][x] = 0;
//                     }
//                 }
//                 return;
//             }
//         }
//     }
//     printGrid(arr);
//     exit(0);
// }

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
    int random = rand();
    solve(a, random, true);
}