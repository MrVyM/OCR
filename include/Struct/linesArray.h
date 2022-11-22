#ifndef LINEARRAY_H
#define LINEARRAY_H

#include "Struct/image.h"
#include "Struct/houghLines.h"

struct LineArray
{
    int length;
    int index;
    Line* value;
};
typedef struct LineArray LineArray;

LineArray initLinesArray(int length);
LineArray appendLinesValue(Line line, LineArray lineArray);
void freeLinesArray(LineArray lineArray);

#endif
