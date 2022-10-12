#include "Struct/matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix* initMatrix(int width, int height) {
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->width = width;
    matrix->height = height;
    float** data = malloc(sizeof(float*) * height); 
    for(int x = 0; x < height; x++){
        data[x] = calloc(width, sizeof(float));
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
            printf("%f ",matrix->value[i][j]);
        printf("\n");
    }
}

void freeMatrix(Matrix* matrix)
{
    for(int h = 0; h < matrix->height; h++)
    {
        free(matrix->value[h]);
    }
    free(matrix->value);
    free(matrix);
}

void addScalarMatrix(Matrix* matrix, float scalar)
{
    for(int i = 0; i < matrix->height; i++)
    {
        for(int j = 0; j < matrix->width; j++)
            matrix->value[i][j] += scalar;
    }
}

void mulScalarMatrix(Matrix* matrix, float scalar)
{
    for(int i = 0; i < matrix->height; i++)
    {
        for(int j = 0; j < matrix->width; j++)
            matrix->value[i][j] *= scalar;
    }
}

void addMatrix(Matrix* m1, Matrix* m2)
{
    
}