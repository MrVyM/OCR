#include <stdio.h>
#include <string.h>
#include <err.h>
#include "sudoku_solver.h"
#include "sudoku_file.h"


int main(int argc, char** argv){
    if(argc != 2)
        errx(1, "The number of arguments is not valid");

    size_t filename_len = strlen(argv[1]);
    char filename[filename_len];
    strcpy(filename, argv[1]);

    unsigned char grid[9][9] = {};
    int result_value = read_sudoku_file(filename, grid);

    if(result_value == 1)
        errx(2, "The file specified in argument doesn't exist");
    else if(result_value == 2)
        errx(3, "The file specified in argument doesn't respect the correct sudoku grid format");
    else if(!solve_sudoku(grid, 0, 0))
        errx(4, "No solution exists for this sudoku grid");

    char result_filename[filename_len + 7];
    strcpy(result_filename, filename);
    strcat(result_filename, ".result");
    write_sudoku_file(result_filename, grid);

    return 0;
}