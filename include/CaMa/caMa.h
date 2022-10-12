#pragma once

#include "structure.h"

Matrix* initMatrix(int width, int height);

void printVector(Vector vect);

void scalarMulVector(Vector* vect, char scalar);

void scalarAddVector(Vector* vect, char scalar);

Vector* dotVector(Vector* vectA, Vector* vectB);

// Multiplication de vecteur
// Exposant de vecteur
