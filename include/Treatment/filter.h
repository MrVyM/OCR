#ifndef FILTER_H
#define FILTER_H

#include "matrix.h"
#include "image.h"

struct Filter
{
	size_t borderSize;
	size_t radius;
	Matrix matrix;
};
typedef struct Filter Filter;

Image* applyFilter(Filter* filter, Image* image);
Filter* createFilter(size_t radius, float (*func)(size_t, size_t));
void freeFilter(Filter* filter);

#endif
