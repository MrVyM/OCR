#pragma once 

#include "matrix.h"

#define LEARNING_RATE 0.1

struct NeuralNetwork
{
	Matrix* hidden;
	Matrix* output;
	Matrix* hiddenBias;
	Matrix* outputBias;
	int numInput;
	int numHidden;
	int numOuput;
};

typedef struct NeuralNetwork NeuralNetwork;

NeuralNetwork* initNetwork(int numInput, int numHidden, int numOuput);

void freeNetwork(NeuralNetwork* network);