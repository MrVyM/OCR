#include <stdio.h>
#include "Struct/neuralNetwork.h"
#include <stdlib.h>

NeuralNetwork* initNetwork(int numInput, int numHidden, int numOuput)
{
	

	NeuralNetwork* network = malloc(sizeof(NeuralNetwork));

	network->hidden = randomMatrix(numHidden,numInput);
	network->output = randomMatrix(numOuput,numHidden);
	network->hiddenBias = randomMatrix(numHidden,1);
	network->outputBias = randomMatrix(numOuput,1);

	network->numHidden = numHidden;
	network->numOuput = numOuput;
	network->numInput = numInput;

	return network;
}