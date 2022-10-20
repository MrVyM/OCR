#ifndef THRESOLDING_H
#define THRESOLDING_H

#include "Struct/image.h"
#include "Struct/matrix.h"

void *generateHistogram(Image *image, int histogram[]);
void applyThresolding(Image *image, int thresold);
double computeOtsuVariance(int histogram[], Image *image, int thresold);
int findThresholdOtsu(int histogram[], Image *image);
void otsuTresolding(Image *image);

#endif