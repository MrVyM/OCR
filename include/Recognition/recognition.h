#pragma once

NeuralNetwork* trainRecognition(NeuralNetwork* net, float (*activ) (float),float (*deriv) (float));

Matrix* recognized(NeuralNetwork* net,float (*activ)(float), float a, float b);

void showStat(NeuralNetwork* net, float (*activ)(float));
