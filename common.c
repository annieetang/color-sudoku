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
    // checking row to make sure the number is possible in the row
    for (int i = 0; i < 9; i++)
    {
        if (arr[y][i] == num)
            return false;
    }

    // checking column to make sure the number is possible in the column
    for (int i = 0; i < 9; i++)
    {
        if (arr[i][x] == num)
            return false;
    }

    // checking square to make sure the number is possible in the square
    // uses int division and 2 for loops to loop over every item in the square x,y is in
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

    // if none of the checks returned false, returns true at end!!
    return true;
}
