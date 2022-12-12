#ifndef SOLVING_H
#define SOLVING_H

void print_sudoku(int** sudoku);
int can_be_placed(int** grid, unsigned char row, unsigned char col, unsigned char num);
int solve_sudoku(int** grid, unsigned char row, unsigned char col);

#endif