#pragma once

Matrix* costFunction(Matrix* solution, Matrix* result);

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ)(float),float (*deriv)(float));

Matrix* recognized(NeuralNetwork* net,float (*activ)(float), Matrix* input);

void showStat(NeuralNetwork* net, float (*activ)(float));
