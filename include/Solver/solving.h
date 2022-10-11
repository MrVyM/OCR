#ifndef SOLVING_H
#define SOLVING_H

void print_sudoku(unsigned char sudoku[9][9]);
int can_be_placed(unsigned char grid[9][9], unsigned char row, unsigned char col, unsigned char num);
int solve_sudoku(unsigned char grid[9][9], unsigned char row, unsigned char col);

#endif