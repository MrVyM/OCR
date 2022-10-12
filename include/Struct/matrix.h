#pragma once

struct Matrix
{
    int width;
    int height;
    char** value;
};

typedef struct Matrix Matrix;

Matrix* initMatrix(int width, int height);

void printMatrix(Matrix* matrix);

