#ifndef FILTER_H
#define FILTER_H

#include "image.h"

struct Filter
{
	size_t borderSize;
	size_t radius;
	float** matrix;
};
typedef struct Filter Filter;

Filter* createEmptyFilter(size_t radius);
Image* applyFilter(Filter* filter, Image* image);
Filter* createFilter(size_t radius, float (*func)(size_t, size_t));
void printFilter(Filter* filter);
void freeFilter(Filter* filter);

#endif