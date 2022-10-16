#include "Struct/image.h"
#include "Struct/pixel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void grayscaleImage(Image *image)
{
    Pixel *pixel;
    Uint8 average;
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            pixel = &image->pixels[x][y];
            average = 0.3 * pixel->red + 0.59 * pixel->green + 0.11 * pixel->blue;
            updateSameColorPixel(pixel, average);
        }
    }
}