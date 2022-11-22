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

void saveWeight(char filename[], NeuralNetwork* net);

NeuralNetwork* loadWeight(char filename[]);

void printNeural(NeuralNetwork* net);

void freeNetwork(NeuralNetwork* network);
