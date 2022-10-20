#ifndef MORPH_H
#define MORPH_H

#include "Struct/image.h"

Image *dilate(Image *image, uint kernelSize);
Image *erode(Image *image, uint kernelSize);
Image *morph(Image *image, uint kernelSize, int mode);

#endif