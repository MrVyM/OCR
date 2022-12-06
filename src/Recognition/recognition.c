#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include "Input/file.h"
#include <stdlib.h>


Matrix* recognized(NeuralNetwork* net,float (*activ)(float), Matrix* input)
{
	Matrix* z0 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
    Matrix* a0 = applyFunctionMatrix(z0, activ);
    Matrix* z1 = addMatrix(mulMatrix(net->hidden2, a0), net->hidden2Bias);
    Matrix* a1 = applyFunctionMatrix(z1, activ);
    Matrix* z2 = addMatrix(mulMatrix(net->output, a1), net->outputBias);
    Matrix* a2 = applyFunctionMatrix(z2, activ);
    return a2;
}

void showStat(NeuralNetwork* net, float (*activ)(float))
{
	printf("Result : \n");
    /*
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <=1; j++)
			printf("%d %d %f\n",i,j,(recognized(net,activ,))->value[0][0]);
    */
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

    Matrix* dZ0;
    Matrix* dZ1;
    Matrix* dZ2;


    Matrix* input = initMatrix(1,784);
    Matrix** list_soluce = malloc(sizeof(struct Matrix) * 10);
    for(int i = 0; i < 10; i++)
    {
        list_soluce[i] = initMatrix(1,10);
        list_soluce[i]->value[0][i] = 1.0;
    }
    Matrix* soluce;

	for(int i = 0; i < max_iter; i++)
	{
	    for(int j = 0; j < training_set; j++)
		{
	        // Forward Prop.
            for(int i = 0; i < 784; i++)
                input->value[i][0] = training_list->value[j][i];
            soluce = list_soluce[(int)(training_list->value[j][i])];
            z0 = addMatrix(mulMatrix(net->hidden1, input), net->hidden1Bias);
            a0 = applyFunctionMatrix(z0, activ);
            z1 = addMatrix(mulMatrix(net->hidden2, a0), net->hidden2Bias);
            a1 = applyFunctionMatrix(z1, activ);
            z2 = addMatrix(mulMatrix(net->output, a1), net->outputBias);
            a2 = applyFunctionMatrix(z2, activ);

            dZ2 = multiplyMatrix(costFunction(soluce, a2), applyFunctionMatrix(z2, deriv)); 
            for(int i = 0; i < net->output->width; i++)
            {
                multiply(net->output->value[0],dZ2, learning_rate);
            }

            dZ1 = multiplyMatrix(mulMatrix(transpose(net->output),dZ2), applyFunctionMatrix(z1, deriv));
            
            for(int i = 0; i < net->hidden2->width; i++)
            {
                multiply(net->hidden2->value[0],dZ1, learning_rate);
            }

            dZ0 = multiplyMatrix(mulMatrix(transpose(net->hidden2),dZ1), applyFunctionMatrix(z0, deriv));
            for(int i = 0; i < net->hidden1->width; i++)
            {
                multiply(net->hidden1->value[0],dZ0, learning_rate);
            }
	    }
        if (i % 100 == 0)
            printf("Iter : %d\n",i);
    }
    freeMatrix(input);
    freeMatrix(z0);
    freeMatrix(z1);
    freeMatrix(z2);

    freeMatrix(a0);
    freeMatrix(a1);
    freeMatrix(a2);

    freeMatrix(dZ0);
    freeMatrix(dZ1);
    freeMatrix(dZ2);
    return net;
}
