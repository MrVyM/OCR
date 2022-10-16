#ifndef IMAGE_H
#define IMAGE_H

#include "Struct/pixel.h"

struct Image
{
    int width;
    int height;
    Pixel **pixels;
};
typedef struct Image Image;

Image *createEmptyImage(int width, int height);
Image *createImageFromSurface(SDL_Surface *surface);
void saveImage(Image *image);
Image *cloneImage(Image *image);
void freeImage(Image *image);

#endif