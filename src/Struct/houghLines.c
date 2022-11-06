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

void setPixel1(Image* image, int x, int y)
{
    Pixel* pixel;
    pixel = &image->pixels[x][y];
    pixel->red = 0;
    pixel->green = 0;
    pixel->blue = 255;

}

void draw_line(Image* image, int w, int h, Line line, Pixel* color,
    int thickness, int draw)
{
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
    
    double diagonal = sqrt(width * width + height * height);

    line.x1 = (int)(cos(line.theta) * line.r) + (int)(diagonal * (-sin(line.theta)));
    line.y1 = (int)(sin(line.theta) * line.r) + (int)(diagonal * cos(line.theta));
    line.x2 = (int)(cos(line.theta) * line.r) - (int)(diagonal * (-sin(line.theta)));
    line.y2 = (int)(sin(line.theta) * line.r) - (int)(diagonal * cos(line.theta)) ;
    /*
    if (line.x1 < 0)
        line.x1 = line.x1 * (-1);
    if(line.y1 < 0)
        line.y1 = line.y1 * (-1);

    if (line.x2 < 0)
        line.x2 = line.x2 * (-1);
    if (line.y2 < 0)
        line.y2 = line.y2 * (-1);
    */
   
    Pixel* pixel;
    pixel = initPixel(255, 0, 0);
    printf("| 1 | x1 = % d et y1 = % d\nx2 = % d et y2 = % d\n", line.x1, line.y1, line.x2, line.y2);
    if(line.x1 == line.x2 || line.y1 == line.y2)
        draw_line(image, width, height, line, pixel, 1, 1);
    
    /*
    // Hauteur maximale de l'accumulateur
    int houghHeight;
    if (height > width)
        houghHeight = (int)(sqrt(2) * height) / 2;
    else
        houghHeight = (int)(sqrt(2) * width) / 2;

    // Centre de l'image
    float centerX = width / 2;
    float centerY = height / 2;

    double tsin = sin(line.theta);
    double tcos = cos(line.theta);

    if (line.theta < M_PI * 0.25 || line.theta > M_PI * 0.75)
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = 0;
        line.y2 = height - 1;

        // Calcul sur l'axe x
        line.x1 = (int) ((((line.r - houghHeight) - ((line.y1 - centerY) * tsin)) / tcos) + centerX);
        line.x2 = (int) ((((line.r - houghHeight) - ((line.y2 - centerY) * tsin)) / tcos) + centerX);
        //printf("x1 = %d x2 = %d SUS \n", line.x1, line.x2);
    }
    else
    {
        // Calcul des coordonées cartésiennes
        line.x1 = 0;
        line.y1 = 0;

        line.x2 = width - 1;
        line.y2 = 0;

        // Calcul sur l'axe y
        line.y1 = (int) ((((line.r - houghHeight) - ((line.x1 - centerX) * tcos)) / tsin) + centerY);
        line.y2 = (int) ((((line.r - houghHeight) - ((line.x2 - centerX) * tcos)) / tsin) + centerY);
        //printf("y1 = %d y2 = %d SUS \n", line.y1, line.y2);
    }
    
    Pixel* pixel;
    pixel = initPixel(255, 0, 0);
    printf("| 2 | x1 = % d et y1 = % d\nx2 = % d et y2 = % d\n", line.x1, line.y1, line.x2, line.y2);
    draw_line(image, width, height, line, pixel, 1, 1);
    
    /*

    Pixel* pixel;

    printf("x1 = % d et y1 = % d\nx2 = % d et y2 = % d\n", line.x1, line.y1, line.x2, line.y2);
    /*
    SDL_Surface* surface = SDL_CreateRGBSurface(0, image->width, image->height, 32, 0, 0, 0, 0);

    if (surface == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);

    if (surface == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_PixelFormat* format = surface->format;
    Uint32* pixels = surface->pixels;

    if (SDL_LockSurface(surface) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            Pixel* pixel = &image->pixels[x][y];
            pixels[y * image->width + x] = SDL_MapRGB(format, pixel->red, pixel->green, pixel->blue);
        }
    }



    SDL_UnlockSurface(surface);

    if (surface == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    Image* image = createEmptyImage(surface->w, surface->h);
    Uint32* pixels = surface->pixels;
    SDL_PixelFormat* format = surface->format;

    if (SDL_LockSurface(surface) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            Pixel* pixel = &image->pixels[x][y];
            SDL_GetRGB(pixels[y * image->width + x], format, &pixel->red, &pixel->green, &pixel->blue);
        }
    }

    SDL_UnlockSurface(surface);
    SDL_FreeSurface(surface);
    */
    /*
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
    if (dx < dy)
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
    */
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