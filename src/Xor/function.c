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
