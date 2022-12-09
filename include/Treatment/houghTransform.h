#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include "Struct/image.h"
#include "Struct/matrix.h"
#include "Struct/line.h"

Matrix *createAccumulator(Image *image);
Line **fillHoughMatrix(Image *image, Matrix *accumulator, int sobel_on, double thresold);
void houghTransform(Image *image, int sobel_on, double thresold);

#endif