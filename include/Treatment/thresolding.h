#ifndef THRESOLDING_H
#define THRESOLDING_H

#include "Struct/image.h"
#include "Struct/matrix.h"

Matrix *generateHistogram(Image *image);
void applyThresolding(Image *image, int thresold);
double computeOtsuVariance(Matrix *histogram, Image *image, int thresold);
int findThresholdOtsu(Matrix *histogram, Image *image);
void otsuTresolding(Image *image);

#endif