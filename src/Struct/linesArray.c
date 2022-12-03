#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Struct/image.h"
#include "Struct/linesArray.h"
#include "Struct/houghLines.h"

LineArray initLinesArray(int length)
{
    LineArray lineArray;
    lineArray.length = length;
    lineArray.index = 0;
    lineArray.value = malloc(length * sizeof(Line));
    if (lineArray.value == NULL)
        errx(-1, "The data cannot be initialize");
    return lineArray;
}

LineArray appendLinesValue(Line line, LineArray lineArray)
{
    lineArray.index += 1;
    if(lineArray.index >= lineArray.length)
        errx(-1, "The data cannot be initialize");
    lineArray.value[lineArray.index] = line;
    return lineArray;
}

void freeLinesArray(LineArray lineArray)
{
    free(lineArray.value);
    //free(lineArray);
}
