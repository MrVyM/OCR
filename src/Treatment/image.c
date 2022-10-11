#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"

Image* createEmptyImage(int width, int height)
{
	Image* image;
    image.width = width;
    image.height = height;
	image.pixels = calloc(width, sizeof(Pixel *));

    if (image.pixels == NULL)
		errx(-1, "Error while allocating a pointer (createEmptyImage)");

    for (size_t x = 0; x < width; x++)
    {
        image.pixels[x] = calloc(height, sizeof(Pixel));
        if (image.pixels[x] == NULL)
			errx(-1, "Error while allocating a pointer (createEmptyImage)");
    }

    for (size_t x = 0; x < width; x++)
    {
        for (size_t y = 0; y < height; y++)
			updatePixelGrayColor(image.pixels[x][y], 255);
    }
	
    return image;
}

Pixel* updatePixelGrayColor(Pixel* pixel, Uint8 color)
{
	pixel.red = color;
	pixel.green = color;
	pixel.blue = color;
}