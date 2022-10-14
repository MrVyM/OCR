#include <stdio.h>
#include <stdlib.h>
#include "Struct/neuralNetwork.h"

int main(void)
{
    NeuralNetwork* net = initNetwork(2,3,1);
    printf("%d",net->numHidden);
    return 0;
}
