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

void setPixel1(Image* image, int x, int y)
{
    Pixel* pixel;
    pixel = &image->pixels[x][y];
    pixel->red = 0;
    pixel->green = 0;
    pixel->blue = 255;

}

void draw_line(Image* image, int w, int h, Line line,
    int thickness, int draw)
{
   // printf("x1 = %d x2 = %d\n", line.x1, line.x2);
    //printf("y1 = %d y2 = %d\n", line.y1, line.y2);
    //printf("Drawing line\n");
    int x0 = line.x1;
    int y0 = line.y1;

    int x1 = line.x2;
    int y1 = line.y2;

    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;

    int err = dx + dy;

    while (1)
    {
        if (0 <= x0 && x0 < w && 0 <= y0 && y0 < h)
        {
            if (draw)
            {
                setPixel(image,x0, y0);

                if (thickness == 2)
                {
                    if (0 <= (x0 + 1) && (x0 + 1) < w && 0 <= (y0 + 1)
                        && (y0 + 1) < h)
                    {
                        setPixel(image, x0 + 1, y0 + 1);
                    }
                    if (0 <= (x0 - 1) && (x0 - 1) < w && 0 <= (y0 - 1)
                        && (y0 - 1) < h)
                    {
                        setPixel(image, x0 - 1, y0 - 1);
                    }
                }
            }
        }

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void drawAndConvert(Line line, int width, int height, Image* image)
{

    // Hauteur maximale de l'accumulateu

    // Centre de l'image
    double tsin = sin(line.theta);
    double tcos = cos(line.theta);


    if((line.theta < M_PI * 0.25 || line.theta > M_PI * 0.75))
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = 0;
        line.y2 = height - 1;

        // Calcul sur l'axe x
	
	line.x1 =(int) line.r / tcos;
	line.x2 =(int) line.r / tcos - line.y2 * tsin / tcos;
        //line.x1 = (int)((((line.r - houghHeight) - ((line.y1 - centerY) * tsin)) / tcos) + centerX);
        //line.x2 = (int)((((line.r - houghHeight) - ((line.y2 - centerY) * tsin)) / tcos) + centerX);
        //printf("x1 = %d x2 = %d \n", line.x1, line.x2);
    }
    else
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = width - 1;
        line.y2 = 0;

        // Calcul sur l'axe y
	//printf("%f",line.r - houghHeight);
	//printf("%f",(line.r - houghHeight) - ((line.x1 - centerX) * tcos));
//	y = cos(t)/sin(t) * x + rho /sin(t)
	line.y1 =(int) line.r/tsin;
	line.y2 =(int) line.r/tsin - tcos / tsin * line.x2;

  //      line.y1 = (int)((((line.r - houghHeight) - ((line.x1 - centerX) * tcos)) / tsin) + centerY);
    //    line.y2 = (int)((((line.r - houghHeight) - ((line.x2 - centerX) * tcos)) / tsin) + centerY);
        printf("y1 = %d y2 = %d \n", line.y1, line.y2);
    }
    
    if (line.x1 < 0)
        line.x1 = 0;
    if (line.y1 < 0)
        line.y1 = 0;

    if (line.x2 < 0)
        line.x2 = 0;
    if (line.y2 < 0)
        line.y2 = 0;
       
    draw_line(image, width, height, line, 1, 5);
}
