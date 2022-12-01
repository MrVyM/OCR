#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Xor/function.h"
#include "Input/file.h"
#include <stdlib.h>


Matrix* recognized(NeuralNetwork* net,float (*activ)(float), float a, float b)
{
	Matrix* a0 = initMatrix(1,2);
    a0->value[0][0] = a;
    a0->value[1][0] = b;
    Matrix* z1 = mulMatrix(net->hidden,a0);
    z1 = addMatrix(z1,net->hiddenBias);
 	Matrix* a1 = applyFunctionMatrix(z1,activ);
 	Matrix* z2 = mulMatrix(net->output,a1);
	z2 = addMatrix(z2,net->outputBias);
	Matrix* a2 = applyFunctionMatrix(z2,activ);
	return a2;
}

void showStat(NeuralNetwork* net, float (*activ)(float))
{
	printf("Result : \n");
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <=1; j++)
			printf("%d %d %f\n",i,j,(recognized(net,activ,i,j))->value[0][0]);
}

void train(NeuralNetwork* net, Matrix* input, float soluce, float learning_rate, float (*activ)(float),float (*deriv)(float))
{
    Matrix* a0 = initMatrix(1,net->hidden->height); 
    // Input -> Hidden
    for(int i = 0; i < net->hidden->height; i++)
    {
        for(int j = 0; j < input->height; j++)
        {
            a0->value[i][0] += input->value[j][0]*net->hidden->value[i][0];
        }
        a0->value[i][0] += net->hiddenBias->value[i][0];
    }
    // hidden -> output
    Matrix* a1 = initMatrix(1, net->output->height);
    for(int i = 0; i < net->output->height; i++)
    {
        for(int j = 0; j < a1->height; j++)
        {
            a1->value[i][0] += a0->value[j][0]*net->output->value[i][0];
        }
        a1->value[i][0] += net->outputBias->value[i][0];
    }

    freeMatrix(a0);
}

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float))
{
	float learning_rate = 0.2;
	int max_iter = 3500;
    FILE* lines = fopen("assets/Dataset/lines.txt", "r");
	float training_set = readNumber(lines);
    fclose(lines);
    Matrix* training_list = readData("assets/Dataset/data.txt", "assets/Dataset/lines.txt");
	
	for(int i = 0; i < max_iter; i++)
	{
	    for(int j = 0; j < training_set; j++)
		{
	        // Forward Prop.
            Matrix* input = initMatrix(1,784);
            for(int i = 0; i < 784; i++)
                input->value[i][0] = training_list->value[j][i];
            train(net, input, training_list->value[i][784], learning_rate, activ, deriv);
            freeMatrix(input);
	    }
	}
    return net;
}
