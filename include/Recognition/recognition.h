#pragma once

void train(NeuralNetwork* net, Matrix* input, float soluce, float learning_rate, float (*activ)(float),float (*deriv)(float)));

Matrix* costFunction(Matrix* solution, Matrix* result);

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ) (float),float (*deriv) (float));

Matrix* recognized(NeuralNetwork* net,float (*activ)(float), float a, float b);

void showStat(NeuralNetwork* net, float (*activ)(float));
