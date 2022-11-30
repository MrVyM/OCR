#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include "Input/file.h"
#include <stdlib.h>
#include <err.h>
#include <string.h>

NeuralNetwork* initNetwork(int numInput, int numHidden, int numOuput)
{
	NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

	if (network == NULL)
		errx(-1,"NeuralNetwork cannot be initialize.");


    network->hidden = randomMatrix(numInput,numHidden,1);
	network->output = randomMatrix(numHidden,numOuput,1);
	network->hiddenBias = randomMatrix(1,numHidden,0);
	network->outputBias = randomMatrix(1,numOuput,0);

	network->numHidden = numHidden;
	network->numOuput = numOuput;
	network->numInput = numInput;

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
        sprintf(s,"%d\n%d\n%d\n",net->numInput,net->numHidden,net->numOuput);
        fputs(s,file);
        fputs(stringMatrix(net->hidden),file); 
        fputs(stringMatrix(net->output),file);
        fputs(stringMatrix(net->hiddenBias),file);
        fputs(stringMatrix(net->outputBias),file);
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
	printf("Hidden :\n");
	printMatrix(net->hidden);
	printf("Output :\n");
	printMatrix(net->output);
	printf("HiddenBias :\n");
	printMatrix(net->hiddenBias);
	printf("OutputBias :\n");
	printMatrix(net->outputBias);
}

void freeNetwork(NeuralNetwork* network)
{
	free(network->hidden);
	free(network->output);
	free(network->hiddenBias);
	free(network->outputBias);

	free(network);
}
