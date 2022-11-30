#pragma once
#include "Struct/matrix.h"

int readNumber(FILE *file);

float readFloat(FILE *file);

Matrix* readData(char data[], char lines[]);
