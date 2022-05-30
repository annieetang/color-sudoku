/* 
 * common.h - header file for common.c that contains functions shared by create and solve
 * 
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdbool.h>

/*
 * printGrid:
 * loops through the 2d sudoku grid and prints the elements
 * in a grid with spaces in between
 */
void printGrid(int (*arr)[9]);

/* checks if this is a writeable file
 */
bool w_file(char *filename);

/*
 * printGrid:into a file specified by filepath
 * loops through the 2d sudoku grid and prints the elements
 * in a grid with spaces in between
 */
void printGrid_into_file(int (*arr)[9], char *filename);

/*
 * possible:
 * takes a 2d array and x and y coordinates for the grid and a number 1-9 as inputs
 * returns false if that number can't go in that coordinate point in the grid
 * because of the numbers in its row, column, or square. otherwise returns true
 */
bool possible(int (*arr)[9], int y, int x, int num);

#endif // __COMMON_H
