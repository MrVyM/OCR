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
        errx(-1,"randomMatrix : the matrix cannot be initialize");
    matrix->width = width;
    matrix->height = height;
    float** data = malloc(sizeof(float*) * height); 
    if (data == NULL)
        errx(-1,"randomMatrix : the line cannot be initialize");
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
    if (matrix == NULL)
        printf("This matrix is NULL\n");
    else
    {
        printf("h : %d w : %d\n",matrix->height,matrix->width);
        for(int i = 0; i < matrix->height; i++)
        {
            printf("%d : ",i);
            for(int j = 0; j < matrix->width; j++)
                printf("%f ",matrix->value[i][j]);
            printf("\n");
        }
    }
}

Matrix* applyFunctionMatrix(Matrix* m1, float(*func)(float))
{
    Matrix* res = initMatrix(m1->width,m1->height);
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
            res->value[i][j] = func(m1->value[i][j]);
    }
    return res;
}


Matrix* transpose(Matrix* matrix)
{
    Matrix* result = initMatrix(matrix->height,matrix->width);
    for(int x = 0; x < matrix->height; x++)
    {
        for(int y = 0; y < matrix->width; y++)
            result->value[y][x] = matrix->value[x][y];  
    }
    result->width = matrix->height;
    result->height = matrix->width;
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

Matrix* multiplyMatrix(Matrix* m1, Matrix* m2)
{
    /*printMatrix(m1);
    printf("\n");
    printMatrix(m2);
    printf("\n\n");*/
    Matrix* res = initMatrix(m1->width,m2->height);
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
            res->value[i][j] = m1->value[i][j] * m2->value[i][j];
    }
    return res;
}

Matrix* addScalarMatrix(Matrix* matrix, float scalar)
{
    Matrix* res = initMatrix(matrix->width,matrix->height);
    for(int i = 0; i < matrix->height; i++)
    {
        for(int j = 0; j < matrix->width; j++)
            res->value[i][j] += scalar;
    }
    return res;
}
Matrix* mulScalarMatrix(Matrix* matrix, float scalar)
{
    for(int i = 0; i < matrix->height; i++)
    {
        for(int j = 0; j < matrix->width; j++)
            matrix->value[i][j] *= scalar;
    }
    return matrix;
}

Matrix* addMatrix(Matrix* m1, Matrix* m2)
{
    if (m1 == NULL)
    {
        m1 = initMatrix(m2->width,m2->height);
        for(int i = 0; i < m2->height; i++)
        {
            for(int j = 0; j < m2->width; j++)
                m1->value[i][j] *= m2->value[i][j];
        }
        return m1;
    } 
    else
    {
        if (m1->height != m2->height || m1->width != m2->width)
            errx(-10,"addMatrix : The size of the matrix is not correct");
        for(int i = 0; i < m1->height; i++)
        {
            for(int j = 0; j < m1->width; j++)
                m1->value[i][j] += m2->value[i][j];
        }
        return m1;
    }
}

void subMatrix(Matrix* m1, Matrix* m2)
{
    if (m1->height != m2->height || m1->width != m2->width)
        errx(-10,"subMatrix : The size of the matrix is not correct");
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m1->width; j++)
            m1->value[i][j] -= m2->value[i][j];
    }
}

Matrix* mulMatrix(Matrix* m1, Matrix* m2)
{
    //if (m1->width != m2->height)
      //  errx(-10,"The matrix cannot be calculate.");
    Matrix* res = initMatrix(m2->width,m1->height);
    
    for(int i = 0; i < m1->height; i++)
    {
        for(int j = 0; j < m2->width; j++)
        {
            for(int k = 0; k < m1->width; k++)
            { 
                //printf("%d , %d , %d\n",i,j,k);
                float a = m1->value[i][k];
                float b = m2->value[k][j];
                res->value[i][j] += a * b;
            }
        }
    }
    /*printf("Final :\n");
    printMatrix(res);*/
    return res; 
}
