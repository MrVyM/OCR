#include "Struct/filter.h"
#include "Struct/image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Image *applyFilter(Filter *filter, Image *image)
{

	Uint8 tempResult[image->width][image->height];

	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			float sum = 0;

			for (int square_i = max(x - filter->radius, 0); square_i < min(x + filter->radius + 1, image->width); square_i++)
			{
				for (int square_j = max(y - filter->radius, 0); square_j < min(y + filter->radius + 1, image->height); square_j++)
				{
					int xFilter = square_i - x + filter->radius;
					int yFilter = square_j - y + filter->radius;
					sum += image->pixels[square_i][square_j].red * filter->matrix->value[xFilter][yFilter];
				}
			}
			tempResult[x][y] = (Uint8)sum;
		}
	}

	for (int x = 0; x < image->width; x++)
	{
		for (int y = 0; y < image->height; y++)
			updateSameColorPixel(&image->pixels[x][y], tempResult[x][y]);
	}

	return image;
}

Filter *createFilter(int radius, float (*func)(int, int), int normalize)
{
	Filter *filter = malloc(sizeof(Filter));

	if (filter == NULL)
		errx(-1, "Error while allocating a pointer (createEmptyImage)");

	filter->radius = radius;
	filter->borderSize = 2 * radius + 1;

	filter->matrix = initMatrix(filter->borderSize, filter->borderSize);

	float sumValues = 0;

	for (int x = 0; x < filter->borderSize; x++)
	{
		for (int y = 0; y < filter->borderSize; y++)
		{
			if (func == NULL)
				filter->matrix->value[x][y] = 0;
			else
			{
				filter->matrix->value[x][y] = (func)(x - radius, y - radius);
				sumValues += filter->matrix->value[x][y];
			}
		}
	}

	if (normalize)
	{
		for (int x = 0; x < filter->borderSize; x++)
		{
			for (int y = 0; y < filter->borderSize; y++)
				filter->matrix->value[x][y] /= sumValues;
		}
	}

	return filter;
}

Filter *createEmptyFilter(int radius)
{
	return createFilter(radius, NULL, 0);
}

void freeFilter(Filter *filter)
{
	freeMatrix(filter->matrix);
	free(filter);
}
