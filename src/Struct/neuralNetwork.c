#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Input/file.h"
#include <stdlib.h>
#include <err.h>
#include <string.h>

NeuralNetwork* initNetwork()
{
	NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

	if (network == NULL)
		errx(-1,"NeuralNetwork cannot be initialize.");


    network->hidden1 = randomMatrix(16,784,1);
    network->hidden2 = randomMatrix(16,16,1);
	network->hidden1Bias = randomMatrix(1,16,0);
    network->hidden2Bias = randomMatrix(1,16,0);
	network->output = randomMatrix(16,10,1);
	network->outputBias = randomMatrix(1,10,0);

	return network;
}

void saveWeight(char filename[], NeuralNetwork* net)
{
    FILE *file = fopen(filename, "w");
        
    if (file == NULL)
    {
        printf("saveWeight : Can't save the network\n");
    }
    else 
    {
        printf("Saving the weight\n");
        char s[50];
        //sprintf(s,"%d\n%d\n%d\n",net->numInput,net->numHidden,net->numOuput);
        fputs(s,file);
        //fputs(stringMatrix(net->hidden),file); 
        //fputs(stringMatrix(net->output),file);
        //fputs(stringMatrix(net->hiddenBias),file);
        //fputs(stringMatrix(net->outputBias),file);
        fclose(file);
    }
}

NeuralNetwork* loadWeight(char filename[])
{
	FILE *file = fopen(filename,"r");
	NeuralNetwork* net = NULL;
	if (file == NULL)
	{
		printf("loadWeight : Can't load the network");
		return net;
	} 
	else 
	{
		net = initNetwork(readNumber(file),readNumber(file),readNumber(file));

	}
	return net;
}

void printNeural(NeuralNetwork* net)
{
	printf("Hidden1 :\n");
	printMatrix(net->hidden1);
	printf("Hidden2 :\n");
	printMatrix(net->hidden2);
	printf("Output :\n");
	printMatrix(net->output);
	printf("HiddenBias1 :\n");
	printMatrix(net->hidden1Bias);
	printf("HiddenBias2 :\n");
	printMatrix(net->hidden2Bias);
	printf("OutputBias :\n");
	printMatrix(net->outputBias);
}

void freeNetwork(NeuralNetwork* network)
{
	free(network->hidden1);
	free(network->hidden1);
	free(network->output);
	free(network->hidden1Bias);
	free(network->hidden2Bias);
	free(network->outputBias);

	free(network);
}
