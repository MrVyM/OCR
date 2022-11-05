#include <stdio.h>
#include <math.h>
#include "Struct/image.h"
#include "Treatment/morph.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Image *dilate(Image *image, uint kernelSize)
{
    return morph(image, kernelSize, -1);
}

Image *erode(Image *image, uint kernelSize)
{
    return morph(image, kernelSize, 1);
}

Image *morph(Image *image, uint kernelSize, int mode)
{
    if(kernelSize % 2 == 0)
        kernelSize++;
    
    int radius = (kernelSize - 1) / 2;
    Uint8 tempResult[image->width][image->height];

	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			uint value = image->pixels[x][y].red;

			for (uint square_i = max(x - radius, 0); square_i < (uint) min(x + radius + 1, image->width); square_i++)
			{
				for (uint square_j = max(y - radius, 0); square_j < (uint) min(y + radius + 1, image->height); square_j++)
				{
                    if(mode < 0)
                        value = min(value, image->pixels[square_i][square_j].red);
                    else
                        value = max(value, image->pixels[square_i][square_j].red);
				}
			}
			tempResult[x][y] = value;
		}
	}

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
			updateSameColorPixel(&image->pixels[x][y], tempResult[x][y]);
	}

	return image;
}