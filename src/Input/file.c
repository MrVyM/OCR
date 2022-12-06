#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Struct/matrix.h"

int readNumber(FILE *file)
{
    int result = 0;

    char sign = 1;

    char readed = fgetc(file);
    if (readed == '-')
        sign = -1;
    else if (readed == 10 || readed == 32)
        return result * sign;
    else if (readed < 48 || readed > 57)
        return result * sign;
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

int readUnsignedNumber(FILE *file, char readed)
{
    int result = 0;
    while ((readed = fgetc(file))!= EOF)
    {
        if (readed == 10 || readed == 32)
            return result;
        if (readed < 48 || readed > 57)
            break;
        result *= 10;
        result += (readed - 48);
    }
    return result;
}

float readFloat(FILE *file)
{

    char readed = fgetc(file);
    char sign = 1;
    if(readed == '|')
{
	return 1;
}
    if (readed == '-')
    {
        sign = -1;
        readed = fgetc(file);
    }
    float result = readUnsignedNumber(file, readed);
    float number = 1;
    while ((readed = fgetc(file))!= EOF)
    {
        if (readed == 10 || readed == 32)
	{
            return result * sign;
	}
        if (readed < 48 || readed > 57)
            break;
        number /= 10.0;
        if (result < 0)
            result -= (float)(readed - 48) * number;
        else 
            result += (float)(readed - 48) * number;
    }
    return result * sign;
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
