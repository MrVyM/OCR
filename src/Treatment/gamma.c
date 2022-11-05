#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"

void applyGamma(Image *image, uint gamma)
{
    double c = gamma / 128;
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            double factor = pow(image->pixels[x][y].red / 255.0, c) * 255;
            if (factor < 0)
                factor = 0;
            else if (factor > 255)
                factor = 255;

            updateSameColorPixel(&image->pixels[x][y], (Uint8)factor);
        }
    }
}