#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Struct/matrix.h"
#include "Solver/solving.h"

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

int readNumber(FILE *file)
{
    int result = 0;

    char sign = 1;

    char readed = fgetc(file);
    if (readed == '-')
        sign = -1;
    else if (readed == 10 || readed == 32)
        return result;
    else if (readed < 48 || readed > 57)
        return result;
    else 
    {
        result *= 10;
        result += (readed - 48);
    }
    while ((readed = fgetc(file))!= EOF)
    {
        if (readed == 10 || readed == 32)
            return result * sign;
        if (readed < 48 || readed > 57)
            break;
        result *= 10;
        result += (readed - 48);
    }
    return result * sign;
}

float readFloat(FILE *file)
{
    float result = readNumber(file);
    char readed;
    float number = 1;
    while ((readed = fgetc(file))!= EOF)
    {
        if (readed == 10 || readed == 32)
            return result;
        if (readed < 48 || readed > 57)
            break;
        number /= 10.0;
        if (result < 0)
            result -= (float)(readed - 48) * number;        
        else 
            result += (float)(readed - 48) * number;
    }
    return result;
}

Matrix* readData(char data[], char lines[])
{
    FILE* lines_file = fopen(lines, "r");
    int number_lines = readNumber(lines_file);
    fclose(lines_file);
    Matrix* dataset = initMatrix(785, number_lines);

    FILE* dataset_file = fopen(data, "r");
    for(int i = 0; i < number_lines; i++)
    {
        for(int j = 0; j < 784; j++)
        {
            dataset->value[i][j] = fgetc(dataset_file) - 48.0;
        }
        dataset->value[i][784] = fgetc(dataset_file) - 48; // Thats the number in the image
        fgetc(dataset_file); // jump the \n
    }
    fclose(dataset_file);
    return dataset;
}
