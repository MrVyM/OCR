#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
