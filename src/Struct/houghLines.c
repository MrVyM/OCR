#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Struct/image.h"
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


void setPixel(Image* image, int x, int y)
{
    Pixel* pixel;
    pixel = &image->pixels[x][y];
    pixel->red = 255;
    pixel->green = 0;
    pixel->blue = 0;

}

void drawAndConvert(Line line, int width, int height, Image* image)
{
    // Hauteur maximale de l'accumulateur
    int houghHeight;
    if (height > width)
        houghHeight = (int)(sqrt(2) * height) / 2;
    else
        houghHeight = (int)(sqrt(2) * width) / 2;

    // Centre de l'image
    float centerX = width / 2;
    float centerY = height / 2;

    if (line.theta < M_PI * 0.25 || line.theta > M_PI * 0.75)
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = 0;
        line.y2 = height - 1;

        // Calcul sur l'axe x
        line.x1 = (int)((((line.r - houghHeight) - ((line.y1 - centerY) * sin(line.theta))) / cos(line.theta)) + centerX);
        line.x2 = (int)((((line.r - houghHeight) - ((line.y2 - centerY) * sin(line.theta))) / cos(line.theta)) + centerX);
        printf("x1 = %d x2 = %d SUS \n", line.x1, line.x2);
    }
    else
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = width - 1;
        line.y2 = 0;

        // Calcul sur l'axe y
        line.y1 = (int)((((line.r - houghHeight) - ((line.x1 - centerX) * cos(line.theta))) / sin(line.theta)) + centerY);
        line.y2 = (int)((((line.r - houghHeight) - ((line.x2 - centerX) * cos(line.theta))) / sin(line.theta)) + centerY);
        printf("y1 = %d y2 = %d SUS \n", line.y1, line.y2);
    }
    Pixel* pixel;

    printf("x1 = % d et y1 = % d\nx2 = % d et y2 = % d\n", line.x1, line.y1, line.x2, line.y2);

    int dx;
    int dy;
    int x;
    int y;
    if (line.x1 < 0 || line.x2 < 0 || line.y1 < 0 || line.y2 < 0)
        return;
    if (line.x1 > line.x2 && line.y1 > line.y2)
    {
        dx = line.x1 - line.x2;
        dy = line.y1 - line.y2;
        x = line.x2;
        y = line.y2;
    }
    else if (line.x1 < line.x2 && line.y1 > line.y2)
    {
        dx = line.x2 - line.x1;
        dy = line.y1 - line.y2;
        x = line.x1;
        y = line.y2;
    }
    else if (line.x1 < line.x2 && line.y1 < line.y2)
    {
        dx = line.x2 - line.x1;
        dy = line.y2 - line.y1;
        x = line.x1;
        y = line.y1;
    }
    else
    {
        dx = line.x1 - line.x2;
        dy = line.y2 - line.y1;
        x = line.x2;
        y = line.y1;
    }
    int lengthOfLine;
    if (dx > dy)
        lengthOfLine = abs(dx);
    else
        lengthOfLine = abs(dy);
    int deltaX;
    int deltaY;
    if (lengthOfLine != 0)
    {
        deltaX = dx / lengthOfLine;
        deltaY = dy / lengthOfLine;
    }
    else
    {
        return;
    }


    if (!(x >= width || x < 0 || y >= height || y < 0))
        setPixel(image, x, y);
    int i = 0;
    while (i <= lengthOfLine)
    {
        x = x + deltaX;
        y = y + deltaY;
        if (!(x >= width || x < 0 || y >= height || y < 0))
     //   printf("x = %d and y = %d \n", x, y);
            setPixel(image, x, y);

        i += 1;
    }
}

void convertToCartesian(Line line, int width, int height)
{
    // Hauteur maximale de l'accumulateur
    int houghHeight;
    if (height > width)
        houghHeight = (int)(sqrt(2) * height) / 2;
    else
        houghHeight = (int)(sqrt(2) * width) / 2;

    // Centre de l'image
    float centerX = width / 2;
    float centerY = height / 2;

    if (line.theta < M_PI * 0.25 || line.theta > M_PI * 0.75)
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = 0;
        line.y2 = height - 1;

        // Calcul sur l'axe x
        line.x1 = (int) ((((line.r - houghHeight) - ((line.y1 - centerY) * sin(line.theta))) / cos(line.theta)) + centerX);
        line.x2 = (int) ((((line.r - houghHeight) - ((line.y2 - centerY) * sin(line.theta))) / cos(line.theta)) + centerX);
        printf("x1 = %d x2 = %d SUS \n", line.x1, line.x2);
    }
    else
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = width -1;
        line.y2 = 0;

        // Calcul sur l'axe y
        line.y1 = (int) ((((line.r - houghHeight) - ((line.x1 - centerX) * cos(line.theta))) / sin(line.theta)) + centerY);
        line.y2 = (int) ((((line.r - houghHeight) - ((line.x2 - centerX) * cos(line.theta))) / sin(line.theta)) + centerY);
        printf("y1 = %d y2 = %d SUS \n", line.y1, line.y2);
    }
}

void drawHoughLine(Line line, int width, int height, Image *image)
{
    Pixel *pixel;
    
    printf("x1 = % d et y1 = % d\nx2 = % d et y2 = % d\n", line.x1, line.y1, line.x2, line.y2);

    int dx;
    int dy;
    int x;
    int y;
    if (line.x1 < 0 || line.x2 < 0 || line.y1 < 0 || line.y2 < 0)
        return;
    if (line.x1 > line.x2 && line.y1 > line.y2)
    {
        dx = line.x1 - line.x2;
        dy = line.y1 - line.y2;
        x = line.x2;
        y = line.y2;
    }
    else if (line.x1 < line.x2 && line.y1 > line.y2)
    {
        dx = line.x2 - line.x1;
        dy = line.y1 - line.y2;
        x = line.x1;
        y = line.y2;
    }
    else if (line.x1 < line.x2 && line.y1 < line.y2)
    {
        dx = line.x2 - line.x1;
        dy = line.y2 - line.y1;
        x = line.x1;
        y = line.y1;
    }
    else
    {
        dx = line.x1 - line.x2;
        dy = line.y2 - line.y1;
        x = line.x2;
        y = line.y1;
    }
    int lengthOfLine;
    if(dx > dy)
        lengthOfLine = abs(dx);
    else
        lengthOfLine = abs(dy);
    int deltaX;
    int deltaY;
    if (lengthOfLine != 0)
    {
        deltaX = dx / lengthOfLine;
        deltaY = dy / lengthOfLine;
    }
    else
    {
        return;
    }
    

    if (x >= width || y >= height)
        return;
    setPixel(image, x, y);
    int i = 0;
    while (i <= lengthOfLine)
    {
        if (x >= width || y >= height)
            break;
        printf("x = %d and y = %d UwU\n", x, y);
        x = x + deltaX;
        y = y + deltaY;

        setPixel(image, x, y);

        i += 1;
    }
    /*
    if (line.x1 < line.x2)
    {
        for (int x = line.x1; x < line.x2; ++x)
        {
            if ((line.x2 - line.x1) != 0)
            {
                y = abs((line.y2 - line.y1) / (line.x2 - line.x1)) * x;
                if (y >= height)
                    break;
            }
        }
    }
    else
    {
        for (int x = line.x2; x < line.x1; ++x)
        {
            if ((line.x2 - line.x1) != 0)
            {
                y = abs((line.y2 - line.y1) / (line.x2 - line.x1)) * x;
                if (y >= height)
                    break;
                pixel = &image->pixels[x][y];
                pixel->red = 255;
                pixel->green = 0;
                pixel->blue = 0;
            }
        }
    }*/
}