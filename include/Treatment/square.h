#ifndef SQUARE_H
#define SQUARE_H

#include "Struct/image.h"
#include "Struct/line.h"
#include "Treatment/houghTransform.h"
#include "Treatment/resize.h"
#include "Treatment/rotation.h"

Image *extractSquare(Image *image, int x1, int y1, int x2, int y2);

int number(int *l);

Image *findBiggest2(Image *image, Line **listeline);

Image **cutImage(Image *image);

int *Imagetoint(Image *image);

int* createTab(Image **tab);

void decoupage(Image *image);

Image* traitement(Image *image, Line**listeline);

int** square(Image* image,Line** listeline);

#endif
