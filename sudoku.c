/* 
 * sudoku.c - a program that generates a valid sudoku for a user to solve, 
 *            and also solves an inputted valid sudoku
 * 
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
#include "create.h"
#include "solve.h"
#include "common.h"

#define formatBool(b) ((b) ? "true" : "false")

/*
 * main - function that parses arguments and passes to other functions to create or solve 
 */ 
int main(int argc, char const *argv[])
{
    if (argc <2 || argc>3)
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
    else if (strcmp(argv[1], "solve") == 0 && argc == 2)
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
    else if (strcmp(argv[1], "solvefile") == 0) {
        //check filename
        char *file = malloc(strlen(argv[2]));
        if (file == NULL) {
            fprintf(stderr, "couldn't allocate memory for a filename passed in");
            return 2;
        }
        strcpy(file, argv[2]);
        if (!w_file(file)) {
            fprintf(stderr, "file passed in is not writable");
            return 2;
        }
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
        solve_into_file(a, &printed, file); // should not need to malloc
        free(file);
        return 0;
    }
    fprintf(stderr, "incorrect format. do this: sudoku [solve|create]\n");
    return 2;
}
