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

    Matrix* z0;
    Matrix* z1;
    Matrix* z2;

    Matrix* a0;
    Matrix* a1;
    Matrix* a2;


	for(int i = 0; i < max_iter; i++)
	{
	    for(int j = 0; j < training_set; j++)
		{
	        // Forward Prop.
            Matrix* input = initMatrix(1,784);
            for(int i = 0; i < 784; i++)
                input->value[i][0] = training_list->value[j][i];
            Matrix* soluce = initMatrix(1,10);
            soluce->value[0][(int)(training_list->value[i][784])] = 1.0;
            a0 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
            z0 = applyFunctionMatrix(a0, activ);
            a1 = addMatrix(mulMatrix(net->hidden2, a0), net->hidden2Bias);
            z1 = applyFunctionMatrix(a1, activ);
            a2 = addMatrix(mulMatrix(net->output, a1), net->outputBias);
            z2 = applyFunctionMatrix(a2, activ);

            Matrix* dZ2 = multiplyMatrix(costFunction(soluce, a2), applyFunctionMatrix(z2, deriv)); 
            for(int i = 0; i < net->output->width; i++)
            {
                multiply(net->output->value[0],dZ2);
            }

            Matrix* dZ1 = multiplyMatrix(mulMatrix(transpose(net->output),dZ2), applyFunctionMatrix(z1, deriv));
            
            for(int i = 0; i < net->hidden2->width; i++)
            {
                multiply(net->hidden2->value[0],dZ1);
            }

            Matrix* dZ0 = multiplyMatrix(mulMatrix(transpose(net->hidden2),dZ1), applyFunctionMatrix(z0, deriv));
            for(int i = 0; i < net->hidden1->width; i++)
            {
                multiply(net->hidden1->value[0],dZ0);
            }
            freeMatrix(input);
	    }
    }
    return net;
}
