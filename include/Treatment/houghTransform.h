#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include "Struct/image.h"
#include "Struct/matrix.h"
#include "Struct/line.h"

Matrix *createAccumulator(Image *image);
Line **fillHoughMatrix(Image *image, Matrix *accumulator);
void houghTransform(Image *image);

#endif