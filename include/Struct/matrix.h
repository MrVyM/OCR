#pragma once

struct Matrix
{
    int width;
    int height;
    float **value;
};

typedef struct Matrix Matrix;

Matrix *initMatrix(int width, int height);

Matrix* randomMatrix(int width, int height, int negative);

char* stringMatrix(Matrix* mat);

void printMatrix(Matrix *matrix);

Matrix* transpose(Matrix* matrix);

void freeMatrix(Matrix* matrix);

void multiply(float* list, Matrix* mulitplier, float learning_rate);

Matrix* addScalarMatrix(Matrix* matrix, float scalar);

Matrix* mulScalarMatrix(Matrix* matrix, float scalar);

Matrix* divScalarMatrix(Matrix* matrix, float scalar);

Matrix* addMatrix(Matrix* m1, Matrix* m2);

Matrix* multiplyMatrix(Matrix* m1, Matrix* m2);

Matrix* subMatrix(Matrix* m1, Matrix* m2);

Matrix* applyFunctionMatrix(Matrix* m1,float(*fc)(float));

Matrix *mulMatrix(Matrix *m1, Matrix *m2);

int maxIndexMatrix(Matrix* m1);