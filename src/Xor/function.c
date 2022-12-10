#include <stdio.h>
#include <math.h>
#include "Struct/matrix.h"


float sigmoid(float z)
{
    return 1/(1 + exp(-z));
}

float relu(float z)
{
    if (z < 0)
        return 0;
    return z;
}

float deriv_sigmoid(float z)
{
    return z*(1 - z);
}

float deriv_relu(float z)
{
    if (z < 0)
        return 0;
    return 1;
}

Matrix* meanSquareError(Matrix* soluce, Matrix* result)
{
    float t = 0;
    Matrix* res = initMatrix(1,soluce->height);
    for(int i = 0; i < soluce->height; i++)
    {   
        t = (result->value[0][i] - soluce->value[0][i]);
        res->value[0][i] = (1/2)*t*t;
    }
    return res;
}


Matrix* meanAbsoluteError(Matrix* soluce, Matrix* result)
{
    float t = 0;
    Matrix* res = initMatrix(1,soluce->height);
    for(int i = 0; i < soluce->height; i++)
    {   
        t = (result->value[0][i] - soluce->value[0][i]);
        res->value[0][i] = t*t;
    }
    return mulScalarMatrix(res,1/2);
}