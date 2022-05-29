/* 
 * create.h - header file for create.c that contains functions to create/generate a sudoku
 * 
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#ifndef __CREATE_H
#define __CREATE_H

#include <stdio.h>
#include <stdbool.h>

/*
 * solutionCounter:
 * solves a given sudoku grid, and each time solved adds to
 * an int at a pointer passed in which keeps track of how many solutions there are
 * so that we can use this while creating a new puzzle that must have a unique solution
 * each recursive call only runs if there have been less than 2 solutions found
 */
void solutionCounter(int (*arr)[9], int *solutions);

/*
 * generatePuzzle:
 * creates an empty sudoku grid and places numbers in the 3 squares
 * diagonally from top left to bottom right. Then calls generatePuzzleHelper
 * on the grid, which solves it and takes numbers out.
 */
void generatePuzzle();

/*
 * generatePuzzleHelper:
 * helper function for generatePuzzle
 */
void generatePuzzleHelper(int (*arr)[9], bool *created);

#endif // __CREATE_H
