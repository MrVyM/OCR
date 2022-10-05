#include "CaMa/caMa.h"
#include <stdio.h>

void printVector(Vector vect) 
{
    printf("Length : %d ; ", vect.length);
    for(int i = 0; i < vect.length; i++)
        printf("%d ", vect.value[i]);
    printf("\n");
}


void scalarMulVector(Vector* vect, char scalar)
{
    for(int i = 0; i < vect->length; i++)
    {
        vect->value[i] *= scalar;
    }
}

void scalarAddVector(Vector* vect, char scalar)
{
    for(int i =0; i < vect->length;i++)
    {
        vect->value[i] += scalar;
    }
}



