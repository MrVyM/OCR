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
    Matrix* m = initMatrix(3,2);
    addScalarMatrix(m,2);
    Matrix* m1 = randomMatrix(2,3);
    //printMatrix(mulMatrix(m,m1));

    freeNetwork(net);
    return 0;
}
