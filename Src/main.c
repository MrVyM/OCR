#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "CaMa/caMa.h"

int main()
{
    printf("Starting : \n");
    char value[] = {0,1,2,4,5,6};
    Vector vect = {5, value};
    scalarVector(&vect,  5);
    
    printVector(vect);
    return(EXIT_SUCCESS);
}

