#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include "Struct/image.h"
#include "Struct/matrix.h"

Matrix *createAccumulator(Image *image);
Matrix *fillHoughMatrix(Image *image, Matrix *accumulator);
void houghTransformBis(Image *image);

#endif