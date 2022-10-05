#include "CaMa/caMa.h"
#include <stdio.h>

void printVector(Vector vect) 
{
    printf("Length : %d ; ", vect.length);
    for(int i = 0; i < vect.length; i++)
        printf("%d ", vect.value[i]);
    printf("\n");
}


void scalarVector(Vector* vect, char scalar)
{
    for(int i = 0; i < vect->length; i++)
    {
        vect->value[i] *= scalar;
    }
}
/*
Vector* dotVector(Vector* vectA, Vector* vectB)
{
    return Vector s = {5; {5,0,0,0,0}};
}
*/
