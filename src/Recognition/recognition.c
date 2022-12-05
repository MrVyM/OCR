#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include "Input/file.h"
#include <stdlib.h>


Matrix* recognized(NeuralNetwork* net,float (*activ)(float), float a, float b)
{
	return NULL;
}

void showStat(NeuralNetwork* net, float (*activ)(float))
{
	printf("Result : \n");
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <=1; j++)
			printf("%d %d %f\n",i,j,(recognized(net,activ,i,j))->value[0][0]);
}

Matrix* costFunction(Matrix* soluce, Matrix* result)
{
    float t = 0;
    Matrix* res = initMatrix(1,soluce->height);
    for(int i = 0; i < soluce->height; i++)
    {   
        t = (result->value[0][i] - soluce->value[0][i]);
        res->value[0][i] = t*t;
    }
    return res;
}

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
    printNeural(net);
	float learning_rate = 0.2;
	int max_iter = 3500;
    FILE* lines = fopen("assets/Dataset/lines.txt", "r");
	float training_set = readNumber(lines);
    fclose(lines);
    Matrix* training_list = readData("assets/Dataset/data.txt", "assets/Dataset/lines.txt");
	
    Matrix* dW0;
    Matrix* dW1;
    Matrix* dW2;

    Matrix* dB0;
    Matrix* dB1;
    Matrix* dB2;

    Matrix* z0;
    Matrix* z1;
    Matrix* z2;

    Matrix* a0;
    Matrix* a1;
    Matrix* a2;


	for(int i = 0; i < max_iter; i++)
	{
        dW0 = NULL;
        dW1 = NULL;
        dW2 = NULL;

        dB0 = NULL;
        dB1 = NULL;
        dB2 = NULL;

	    for(int j = 0; j < training_set; j++)
		{
	        // Forward Prop.
            Matrix* input = initMatrix(1,784);
            for(int i = 0; i < 784; i++)
                input->value[i][0] = training_list->value[j][i];
            Matrix* soluce = initMatrix(1,10);
            soluce->value[0][(int)(training_list->value[i][784])] = 1.0;
            a0 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
            printf("end\n");
            z0 = applyFunctionMatrix(a0, activ);
            a1 = addMatrix(mulMatrix(net->hidden2, a0), net->hidden2Bias);
            z1 = applyFunctionMatrix(a1, activ);
            a2 = addMatrix(mulMatrix(net->output, a1), net->outputBias);
            z2 = applyFunctionMatrix(a2, activ);


            Matrix* dZ2 = multiplyMatrix(costFunction(soluce, a2), applyFunctionMatrix(z2, deriv)); 
            dB2 = addMatrix(dB2, dZ2);
            dW2 = addMatrix(dW2,mulMatrix(a2,dZ2));
            
            Matrix* dZ1 = multiplyMatrix(mulMatrix(transpose(net->output),dZ2), applyFunctionMatrix(z1, deriv));
            dB1 = addMatrix(dB1, dZ1);
            dW1 = addMatrix(dW1,mulMatrix(a1,dZ1));

            Matrix* dZ0 = multiplyMatrix(mulMatrix(transpose(net->hidden2),dZ1), applyFunctionMatrix(z0, deriv));
            dB0 = addMatrix(dB0, dZ0);
            dW0 = addMatrix(dW0, mulMatrix(a0,dZ0));

            freeMatrix(input);
	    }
        printMatrix(dW2);
        printMatrix(net->output);
        net->output = subMatrix(net->output,mulScalarMatrix(divScalarMatrix(dW2, training_set),learning_rate));
        printf("ökay\n");
        net->outputBias = subMatrix(net->outputBias,mulScalarMatrix(divScalarMatrix(dB2, training_set),learning_rate));
        net->hidden2Bias = subMatrix(net->hidden2Bias,mulScalarMatrix(divScalarMatrix(dB1, training_set),learning_rate));
        net->hidden2 = subMatrix(net->hidden2,mulScalarMatrix(divScalarMatrix(dW1, training_set),learning_rate));
        printMatrix(net->hidden1);
        printMatrix(mulScalarMatrix(divScalarMatrix(dW0, training_set),learning_rate));
        net->hidden1 = subMatrix(net->hidden1,mulScalarMatrix(divScalarMatrix(dW0, training_set),learning_rate));
        net->hidden1Bias = subMatrix(net->hidden1Bias,mulScalarMatrix(divScalarMatrix(dB0, training_set),learning_rate));
	}
    return net;
}
