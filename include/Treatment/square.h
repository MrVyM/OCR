#ifndef SQUARE_H
#define SQUARE_H

#include "Struct/image.h"
#include "Struct/line.h"
#include "Treatment/houghTransform.h"
#include "Treatment/resize.h"

int** square(Image* image,Line** listeline);

#endif
