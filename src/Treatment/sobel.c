#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include <stdio.h>
#include <math.h>

Image *sobelOperator(Image *image)
{
	Matrix *Gx = initMatrix(3, 3);
	Gx->value[0][0] = 1;
	Gx->value[1][0] = 0;
	Gx->value[2][0] = -1;

	Gx->value[0][1] = 2;
	Gx->value[1][1] = 0;
	Gx->value[2][1] = -2;

	Gx->value[0][2] = 1;
	Gx->value[1][2] = 0;
	Gx->value[2][2] = -1;

	Matrix *Gy = initMatrix(3, 3);
	Gy->value[0][0] = 1;
	Gy->value[1][0] = 2;
	Gy->value[2][0] = 1;

	Gy->value[0][1] = 0;
	Gy->value[1][1] = 0;
	Gy->value[2][1] = 0;

	Gy->value[0][2] = -1;
	Gy->value[1][2] = -2;
	Gy->value[2][2] = -1;

	int height = image->height;
	int width = image->width;

	for (int col = 0; col < height; ++col)
	{
		for (int row = 0; row < width; ++row)
		{
			double magX = 0.0;
			double magY = 0.0;

			for (int a = 0; a < 3; ++a)
			{
				for (int b = 0; b < 3; ++b)
				{
					if (a + row >= 0 && b + col >= 0 && a + row < width && b + col < height)
					{
						magX += (image->pixels[a + row][b + col].red) * Gx->value[a][b];
						magY += (image->pixels[a + row][b + col].red) * Gy->value[a][b];
					}
				}
			}
			int val = (int)sqrt((magX * magX) + (magY * magY));
			if (val > 128)
				val = 255;
			else
				val = 0;
			image->pixels[row][col].red = val;
			image->pixels[row][col].green = val;
			image->pixels[row][col].blue = val;
		}
	}
	return image;
}