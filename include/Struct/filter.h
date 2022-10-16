#ifndef FILTER_H
#define FILTER_H

#include "matrix.h"
#include "image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct Filter
{
    int borderSize;
    int radius;
    Matrix *matrix;
};
typedef struct Filter Filter;

Image *applyFilter(Filter *filter, Image *image);
Filter *createFilter(int radius, float (*func)(int, int), int normalize);
Filter *createEmptyFilter(int radius);
void freeFilter(Filter *filter);

#endif