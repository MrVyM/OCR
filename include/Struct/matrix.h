#pragma once

struct Matrix
{
    int width;
    int height;
    float** value;
};

typedef struct Matrix Matrix;

Matrix* initMatrix(int width, int height);

Matrix* randomMatrix(int width, int height);

void printMatrix(Matrix* matrix);

Matrix* transpose(Matrix* matrix);

void freeMatrix(Matrix* matrix);

void addScalarMatrix(Matrix* matrix, float scalar);

void mulScalarMatrix(Matrix* matrix, float scalar);

void addMatrix(Matrix* m1, Matrix* m2);

void applyFunctionMatrix(Matrix* m1,(float)(*fc)(float))

Matrix* mulMatrix(Matrix* m1, Matrix* m2);
