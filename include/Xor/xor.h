#pragma once

NeuralNetwork* trainXor(NeuralNetwork* net, float (*activ) (float));

Matrix* useNetwork(NeuralNetwork* net,float (*activ)(float), float a, float b);
