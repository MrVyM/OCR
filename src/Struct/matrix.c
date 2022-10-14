#include "Struct/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

Matrix* initMatrix(int width, int height) {
    Matrix* matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
        errx(-1,"The matrix cannot be initialize");
    matrix->width = width;
    matrix->height = height;
    float** data = malloc(sizeof(float*) * height); 
    if (data == NULL)
        errx(-1,"The data cannot be initialize");
    for(int x = 0; x < height; x++){
        data[x] = calloc(width, sizeof(float));
    }
    matrix->value = data;
    return matrix;
}

Matrix* randomMatrix(int width, int height) {
    Matrix* matrix = malloc(sizeof(Matrix));
    if (matrix == NULL)
        errx(-1,"The matrix cannot be initialize");
    matrix->width = width;
    matrix->height = height;
    float** data = malloc(sizeof(float*) * height); 
    if (data == NULL)
        errx(-1,"The data cannot be initialize");
    for(int x = 0; x < height; x++){
        data[x] = calloc(width, sizeof(float));
        for(int y = 0; y < width; y++)
            data[x][y] = (float)rand()/RAND_MAX;
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

Matrix* transpose(Matrix* matrix)
{
    Matrix* result = initMatrix(matrix->height,matrix->width);
    for(int x = 0; x < matrix->height; x++)
    {
        for(int y = 0; y < matrix->width; y++)
            result->value[y][x] = matrix->value[x][y];  
    }
    freeMatrix(matrix);
    return result;
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
    if (m1->height != m2->height || m1->width != m2->width)
        exit(-10);
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
            m1->value[i][j] += m2->value[i][j];
    }
}

Matrix* mulMatrix(Matrix* m1, Matrix* m2)
{
    if (m2->height != m1->width)
        exit(-11);
    Matrix* result = initMatrix(m1->height,m2->width);
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j <m2->width; j++)
        {
            for(int k = 0; k < m1->width; k++)
                result->value[i][j] += m1->value[i][k] * m2->value[k][j];
        }
    }
    return result;
}
