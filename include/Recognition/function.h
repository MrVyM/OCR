#pragma once

float sigmoid(float z);

float relu(float z);

float deriv_sigmoid(float z);

float deriv_relu(float z);

Matrix* meanAbsoluteError(Matrix* soluce, Matrix* result);

Matrix* meanSquareError(Matrix* soluce, Matrix* result);
