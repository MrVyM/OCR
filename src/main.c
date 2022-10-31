#include <stdio.h>
#include <stdlib.h>
#include "Struct/neuralNetwork.h"
#include "Xor/xor.h"
#include "Struct/matrix.h"
#include "Xor/function.h"

int main(void)
{
    printf("test\n");
    NeuralNetwork* net = initNetwork(2,3,1);
    //printNeural(net);
    trainXor(net,sigmoid);  
    showResult(net,sigmoid);
    freeNetwork(net);
    return 0;
}
