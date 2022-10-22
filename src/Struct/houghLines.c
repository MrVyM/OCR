#include <stdlib.h>
#include <err.h>
#include "Struct/houghLines.h"


Line initHoughLine (double theta, double r, int score)
{
    Line line;
    line.theta = theta ;
    line.r = r;
    line.score = score;
    line.x1;
    line.y1;
    line.x2;
    line.y2;

    return line;
}

void convertToCartesian(Line line, int width, int height)
{
    // Hauteur maximale de l'accumulateur
    int houghHeight;
    if (height > width)
        houghHeight = (int)(sqrt(2) * height) / 2;
    else
        houghHeight = (int)(sqrt(2) * width) / 2;

    float centerX;
    // TODO
}