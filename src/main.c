#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
#include "Treatment/blur.h"
#include "Treatment/rotation.h"
#include "Treatment/resize.h"
#include "Treatment/thresolding.h"
#include "Treatment/sobel.h"
#include "Treatment/morph.h"
#include "Treatment/contrast.h"
#include "Treatment/gamma.h"
#include "Treatment/hough.h"
#include "Treatment/houghTransform.h"
#include <err.h>
#include "Struct/neuralNetwork.h"
#include "Struct/matrix.h"
#include "Xor/function.h"
#include "Recognition/recognition.h"
#include "Solver/solving.h"
#include "Input/file.h"
#include "Input/recompose.h"


int main(int argc, char** argv){
    if(argc != 2)
        errx(1, "The number of arguments is not valid");

    size_t filename_len = strlen(argv[1]);
    char filename[filename_len];
    strcpy(filename, argv[1]);

    unsigned char grid[9][9] = {};
    unsigned char initial[9][9] = {};
    read_sudoku_file(filename, initial);
    int result_value = read_sudoku_file(filename, grid);

    if(result_value == 1)
        errx(2, "The file specified in argument doesn't exist");
    else if(result_value == 2)
        errx(3, "The file specified in argument doesn't respect the correct sudoku grid format");
    else if(!solve_sudoku(grid, 0, 0))
        errx(4, "No solution exists for this sudoku grid");

    char result_filename[filename_len + 7];
    strcpy(result_filename, filename);
    strcat(result_filename, ".bmp");
    write_sudoku_image(result_filename, grid, initial);

    return 0;
}
