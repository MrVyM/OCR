#include <stdlib.h>
#include <err.h>
#include "Struct/houghLines.h"


Line *initHoughLine (double theta, double r, int width, int height, int score)
{
    Line *line = malloc(sizeof(Line));

    if (line == NULL)
        errx(-1, "Error while allocating a pointer (initHoughLine)");

    line->theta = theta ;
    line->r = r;
    line->score = score;

    return line;
}

void freeLine(Line *line)
{
    free(line);
}