#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"

void applyContrast(Image *image, uint contrast)
{
    double c = contrast > 128 ? 128 : contrast;
    double factor = (259 * (c + 255)) / (255 * (259 - c));

    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            double result = factor * (image->pixels[x][y].red - 128) + 128;
            if (result < 0)
                result = 0;
            else if (result > 255)
                result = 255;

            updateSameColorPixel(&image->pixels[x][y], (Uint8)result);
        }
    }
}