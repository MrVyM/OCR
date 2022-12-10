#pragma once

float sigmoid(float z);

float relu(float z);

float deriv_sigmoid(float z);

float deriv_relu(float z);

Matrix* costFunction(Matrix* soluce, Matrix* result);
