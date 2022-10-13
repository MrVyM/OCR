#include <stdio.h>
#include "Struct/matrix.h"


int train()
{
    Matrix* mIn = initMatrix(4,2);
    Matrix* mOut = initMatrix(4,1);

    int inUnit = 2;
    int hidUnit = 3;
    int outUnit = 1;

    float learning = 0.1;
    int iter = 3500;
    int train_set = 4;

    Matrix* W1 = randomMatrix(hidUnit,inUnit);
    Matrix* W2 = randomMatrix(outUnit, hidUnit);

    Matrix* B1 = randomMatrix(hidUnit,1);
    Matrix* B2 = randomMatrix(outUnit,1);

    int dW1 = 0;
    int dW2 = 0;

    int dB1 = 0;
    int dB2 = 0;

    for(int i = 0; i < iter; i ++)
    {
        dW1 = 0;
        dW2 = 0;

        dB1 = 0;
        dB2 = 0;
        for(int j = 0; j < train_set; j++)
        {
            printf("test");   
        }
    }
}
