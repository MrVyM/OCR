#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include <stdlib.h>
#include <err.h>

NeuralNetwork* initNetwork(int numInput, int numHidden, int numOuput)
{
	NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

	if (network == NULL)
		errx(-1,"NeuralNetwork cannot be initialize.");


    network->hidden = randomMatrix(numInput,numHidden);
	network->output = randomMatrix(numHidden,numOuput);
	network->hiddenBias = randomMatrix(1,numHidden);
	network->outputBias = randomMatrix(1,numOuput);

	network->numHidden = numHidden;
	network->numOuput = numOuput;
	network->numInput = numInput;

	return network;
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
