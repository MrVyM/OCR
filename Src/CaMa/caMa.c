#include "CaMa/CaMa.h"
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
    printf("CC");
}


