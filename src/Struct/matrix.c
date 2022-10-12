#include "Struct/matrix.h"
#include <stdio.h>
#include <stdlib.h>

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