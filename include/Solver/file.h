#ifndef SUDOKU_FILE_H
#define SUDOKU_FILE_H

int read_sudoku_file(char filename[], unsigned char grid[9][9]);
void write_sudoku_file(char filename[], unsigned char grid[9][9]);

#endif