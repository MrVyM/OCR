#include "CaMa/caMa.h"
#include <stdio.h>
#include <stdlib.h>

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

Matrix* initMatrix(int width, int height) {
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->width = width;
    matrix->height = height;
    char** data = malloc(sizeof(char*) * height); 
    for(int x = 0; x < height; x++){
        data[x] = calloc(width, sizeof(char));
    }
    matrix->value = data;
    return matrix;
}


void printMatrix(Matrix* matrix)
{
    for(int i = 0; i < matrix->height; i++)
    {
        printf("%d : ",i);
        for(int j = 0; j < matrix->width; j++)
            printf("%d ",matrix->value[i][j])
        printf("\n");
    }
}