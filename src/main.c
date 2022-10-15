#include <stdio.h>
#include <stdlib.h>
#include "Struct/neuralNetwork.h"
#include "Xor/xor.h"
#include "Struct/matrix.h"
#include "Xor/function.h"

int main(void)
{
    NeuralNetwork* net = initNetwork(2,3,1);
    trainXor(net);   
    freeNetwork(net);
    return 0;
}
