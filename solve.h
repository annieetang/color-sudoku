/* 
 * solve.h - header file for solve.c that contains functions to solve a sudoku
 * 
 * Devon Starr, Annie Tang, Amanda Sun, CS50 Spring 2022
 */

#ifndef __SOLVE_H
#define __SOLVE_H

#include <stdio.h>
#include <stdbool.h>

/*
 * solve:
 * takes a 2d array, a random seed, and a generating bool as inputs
 * random seed is used so that the algorithm doesn't give solve the grid in the
 * same order every time, so that when a puzzle is generated it's random
 * if bool generating is true it removes a bunch of numbers before printing the
 * grid at the end
 * exits execution at the end of the function so that recursion stops solving other solutions
 */
void solve(int (*arr)[9], bool *printedOneSolution);

/*
 * solve, and print into a file
 *
 */
void solve_into_file(int (*arr)[9], bool *printedOneSolution, char *filename);
/* 
 * checkGrid: 
 * checks if the grid inputted to solve is valid 
 * integers are 0-9 and is a 9 by 9 grid
 */ 
bool checkGrid(int (*arr)[9]);

#endif // __SOLVE_H
