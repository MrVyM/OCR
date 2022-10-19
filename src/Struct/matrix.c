#include "Struct/matrix.h"
#include <stdio.h>
#include <stdlib.h>

Matrix *initMatrix(int width, int height)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->width = width;
    matrix->height = height;
    float **mat = (float **)malloc(height * sizeof(float *));
    for (int i = 0; i < height; i++)
        mat[i] = (float *)malloc(width * sizeof(float));
    matrix->value = mat;
    for(int x = 0; x < matrix->height; x++)
    {
        for(int y = 0; y < matrix->width; y++)
        {
            //printf("x : %5d | y : %5d\n ", x, y);
            matrix->value[x][y] = 0;
        }
    }
    return matrix;
}

Matrix *randomMatrix(int width, int height)
{
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->width = width;
    matrix->height = height;
    float **data = malloc(sizeof(float *) * height);
    for (int x = 0; x < height; x++)
    {
        data[x] = calloc(width, sizeof(float));
        for (int y = 0; y < width; y++)
            data[x][y] = (float)rand() / RAND_MAX;
    }
    matrix->value = data;
    return matrix;
}

void printMatrix(Matrix *matrix)
{
    for (int i = 0; i < matrix->height; i++)
    {
        printf("%d : ", i);
        for (int j = 0; j < matrix->width; j++)
            printf("%f ", matrix->value[i][j]);
        printf("\n");
    }
}

void freeMatrix(Matrix *matrix)
{
    for (int h = 0; h < matrix->height; h++)
    {
        free(matrix->value[h]);
    }
    free(matrix->value);
    free(matrix);
}

void addScalarMatrix(Matrix *matrix, float scalar)
{
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->width; j++)
            matrix->value[i][j] += scalar;
    }
}

void mulScalarMatrix(Matrix *matrix, float scalar)
{
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->width; j++)
            matrix->value[i][j] *= scalar;
    }
}

void addMatrix(Matrix *m1, Matrix *m2)
{
    if (m1->height != m2->height || m1->width != m2->width)
        exit(-10);
    for (int i = 0; i < m1->height; i++)
    {
        for (int j = 0; j < m1->width; j++)
            m1->value[i][j] += m2->value[i][j];
    }
}

Matrix *mulMatrix(Matrix *m1, Matrix *m2)
{
    if (m2->height != m1->width)
        exit(-11);
    Matrix *result = initMatrix(m1->height, m2->width);
    for (int i = 0; i < m1->height; i++)
    {
        for (int j = 0; j < m2->width; j++)
        {
            for (int k = 0; k < m1->width; k++)
                result->value[i][j] += m1->value[i][k] * m2->value[k][j];
        }
    }
    return result;
}
