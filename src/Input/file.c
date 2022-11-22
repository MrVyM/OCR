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

float readFloat(FILE *file)
{
    float result = 0.0;
    char readed;
    char number = 0;
    while ((readed = fgetc(file))!= EOF)
    {
        printf("%c %d %f\n",readed,readed,result);
        
        if (readed == 10 || readed == 32)
            return result;
        if (readed != 46 && (readed < 48 || readed > 57))
            break;
        printf("num : %f\n",number);
        if (readed == 46)
        {
            number = 1;   
        }
        else if (number)
        {
            number *= 1/10;
            printf("res : %f\n",number);
            printf("%f\n",number);
            result += (float)(readed - 48) * number;
        }
        else
        {
            printf("behind\n");
            result *= 10.0;
            result += (float)(readed - 48);
        }

        
    }
    return result;
}
