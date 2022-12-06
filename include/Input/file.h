#pragma once
#include "Struct/matrix.h"

int readNumber(FILE *file);

int read_sudoku_file(char filename[], unsigned char grid[9][9]);

void write_sudoku_file(char filename[], unsigned char grid[9][9]);

float readFloat(FILE *file);

Matrix* readData(char data[], char lines[]);
