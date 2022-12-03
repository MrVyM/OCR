#pragma once 

#include "matrix.h"

#define LEARNING_RATE 0.1

struct NeuralNetwork
{
	Matrix* hidden1;
	Matrix* hidden2;
	Matrix* output;
	Matrix* hidden1Bias;
	Matrix* hidden2Bias;
	Matrix* outputBias;
	int numInput;
	int numHidden;
	int numOuput;
};

typedef struct NeuralNetwork NeuralNetwork;

NeuralNetwork* initNetwork();

void saveWeight(char filename[], NeuralNetwork* net);

NeuralNetwork* loadWeight(char filename[]);

void printNeural(NeuralNetwork* net);

void freeNetwork(NeuralNetwork* network);
