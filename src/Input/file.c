#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readNumber(FILE *file)
{
    int result = 0;
    char readed;
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
