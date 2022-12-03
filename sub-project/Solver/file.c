#include <stdio.h>
#include "solving.h"

/*******************************************************************************
 * Allows to read a sudoku grid from a file who has the name "filename"
 *
 * @param filename The name of the file where we want to read the sudoku
 * @param grid     The array where we want to put the sudoku grid read
 * @return int     0 if the file was successfully read
 *                 1 if the file doesn't exist
 *                 2 if the file doesn't respect the sudoku grid format
 ******************************************************************************/
int read_sudoku_file(char filename[], unsigned char grid[9][9])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 1;
    else
    {
        char readed_char;
        int cursor = 0;
        while ((readed_char = fgetc(file)) != EOF)
        {
            if (readed_char == 32 || readed_char == 10)
                continue;
            if (readed_char != 46 && (readed_char < 49 || readed_char > 57))
                break;
            if (readed_char == 46)
                grid[cursor / 9][cursor % 9] = 0;
            else
                grid[cursor / 9][cursor % 9] = readed_char - 48;
            cursor++;
        }
        fclose(file);
        if (cursor == 81)
            return 0;
        else
            return 2;
    }
}

/*******************************************************************************
 * Allows to save a sudoku grid in a file who has the name "filename"
 *
 * @param filename The name of the file where we want to save the sudoku
 * @param grid     The sudoku grid to save in the filename file
 ******************************************************************************/
void write_sudoku_file(char filename[], unsigned char grid[9][9])
{
    FILE *file = fopen(filename, "w");

    for (unsigned char x = 0; x < 9; x++)
    {
        char text[] = "... ... ...\n";
        for (unsigned char y = 0; y < 9; y++)
            text[y + y / 3] = grid[x][y] + 48;
        if (x == 3 || x == 6)
            fputs("\n", file);
        fputs(text, file);
    }

    fclose(file);
}
