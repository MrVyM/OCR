#ifndef SQUARE_H
#define SQUARE_H

#include "Struct/image.h"
#include "Struct/houghLines.h"

Image* extractSquare(Image *image, int x1, int y1, int x2, int y2);

int* findSquare2(Line* listeline, int len);

int[784] caseInt(Image* image);

Image* Cut(Image* image);

int[9][9] result(Image* image);

int[9][9] square(Image* image,Line* listeline);

#endif
