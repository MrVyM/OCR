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
};

typedef struct NeuralNetwork NeuralNetwork;

NeuralNetwork* initNetwork();

void saveWeight(char hidden1_c[], char hidden2_c[], char output_c[], NeuralNetwork* net);

NeuralNetwork* loadWeight(char hidden1_c[], char hidden2_c[], char output_c[]);

void printNeural(NeuralNetwork* net);

void freeNetwork(NeuralNetwork* network);
