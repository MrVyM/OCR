#ifndef ROTATION_H
#define ROTATION_H

#include "Struct/image.h"

void calculate_size(int a, int b, double theta, int *width, int *height);
Image *rotateImage(Image *image, double angle);

#endif