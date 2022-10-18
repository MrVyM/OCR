#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include <stdlib.h>
#include <err.h>

NeuralNetwork* initNetwork(int numInput, int numHidden, int numOuput)
{
	NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

	if (network == NULL)
		errx(-1,"NeuralNetwork cannot be initialize.");


    network->hidden = randomMatrix(numHidden,numInput);
	network->output = randomMatrix(numOuput,numHidden);
	network->hiddenBias = randomMatrix(1,numHidden);
	network->outputBias = randomMatrix(1,numOuput);

	network->numHidden = numHidden;
	network->numOuput = numOuput;
	network->numInput = numInput;

	return network;
}

void freeNetwork(NeuralNetwork* network)
{
	free(network->hidden);
	free(network->output);
	free(network->hiddenBias);
	free(network->outputBias);

	free(network);
}
