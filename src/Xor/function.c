#include <stdio.h>
#include <math.h>

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