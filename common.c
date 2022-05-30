/* 
 * common.h - file that contains functions shared by create and solve
 * 
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* see common.h for descriptions */
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

/* see common.h for descriptions */
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
