#ifndef BLUR_H
#define BLUR_H

#include "Struct/image.h"

float twoDimensionalGaussian(int x, int y);
void applyGaussianBlur(Image *image);

#endif