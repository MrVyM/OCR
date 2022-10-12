#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "filter.h"

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Image* applyFilter(Filter* filter, Image* image)
{
	
	Uint8 tempResult[image.width][image.height];
	
	for(ssize_t x = 0; x < image.width; x++)
	{
		for(ssize_t y = 0; y < image.height; y++)
		{
			float sum = 0;
			
			for(ssize_t square_i = max(x - filter.radius, 0); square_i < min(x + filter.radius + 1, image.width); square_i++)
			{
				for(ssize_t square_j = max(y - filter.radius, 0); square_j < min(y + filter.radius + 1, image.height); square_j++)
				{
					ssize_t xFilter = square_i - x + radius;
					ssize_t yFilter = square_j - y + radius;         
					sum += image.pixels[square_j][square_i] * filter.matrix[xFilter][yFilter];
				}
			}
			tempResult[x][y] = (Uint8) sum;
		}
	}
	
	for(size_t x = 0; x < image.width; x++)
	{
		for(size_t y = 0; y < image.height; y++)
			updatePixelGrayColor(image.pixels[x][y], tempResult[x][y]);
	}
	
	return image;
}

Filter* createFilter(size_t radius, float (*func)(size_t, size_t), int normalize)
{
	Filter* filter;
	filter.radius = radius;
	filter.borderSize = 2 * radius + 1;
	
	filter.matrix = malloc(borderSize,sizeof(float));
	
	if (filter.matrix == NULL)
		errx(-1, "Error while allocating a pointer (createFilter)");
	
    for (size_t x = 0; x < borderSize; x++)
    {
        filter.matrix[x] = calloc(borderSize, sizeof(float));
        if (filter.matrix[x] == NULL)
			errx(-1, "Error while allocating a pointer (createFilter)");
    }
	
	float sumValues = 0;
	
    for (size_t x = 0; x < borderSize; x++)
    {
        for (size_t y = 0; y < borderSize; y++)
		{
			if(func == NULL)
				filter.matrix[x][y] = 0;
			else
			{
				filter.matrix[x][y] = (*func) (x-radius)(y-radius);
				sumValue += filter.matrix[x][y]
			}
		}
    }
	
	if(normalize)
	{
		for (size_t x = 0; x < borderSize; x++)
		{
			for (size_t y = 0; y < borderSize; y++)
				filter.matrix[x][y] /= sumValues;
		}
	}
	
	return filter;
}

Filter* createEmptyFilter(size_t radius)
{
	return createFilter(radius, NULL, 0);
}

void printFilter(Filter* filter)
{
	for(size_t x = 0; x < filter.borderSize; x++)
	{
		for(size_t y = 0; y < filter.borderSize; y++)
			printf("%f ", filter.matrix[x][y]);
		printf("\n");
	}
}

void freeFilter(Filter* filter)
{
	freeMatrix(filter.matrix);
}
