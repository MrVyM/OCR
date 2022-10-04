#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "CaMa/CaMa.h"

int main()
{
    printf("Starting : \n");
    Vector vect = {5,{0,1,2,4,5}};
    scalarVector(&vect,  5);
    printVector(vect);
    return(EXIT_SUCCESS);
}

