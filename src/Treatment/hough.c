// 3 étapes:
// - Pour chaque point de contour détécté, détermination de la courbe
// - Construction de l'accumulateur (les maxima locaux de cette matrice correspondant à des droites probables)
// - Detection des pics dans l'accumulateur

// Include
#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

// Definition des constantes

#define maxTheta 180

// Construction de l'accumulateur

Matrix *Constructor(Image* image)
{
	int width = image->width;
	int height = image->height;

	// Hauteur maximale de l'accumulateur
	int houghHeight;
	if (height > width)
		houghHeight = (int) (sqrt(2) * height) / 2;
	else
		houghHeight = (int) (sqrt(2) * width) / 2;

	// Création de l'accumulateur
	Matrix * acc = initMatrix(maxTheta,height*2);
	
	// Les coordonées du centre de l'image
	centerX = width / 2;
	centerY = height / 2;

	// Count le nombre de points remarquables
	numPoints = 0;

	int *sinArray = malloc(sizeof(int) * maxTheta);
	int *cosArray = malloc(sizeof(int) * maxTheta);

	// Le pas de theta
	int Theta = M_PI / maxTheta;

	for (int i = ; i < axTheta; ++i)
	{
		double theta = i * theta;
		sinArray[i] = (int) cos(theta);
		cosArray[i] = (int) sin(theta);
	}

	// Add points

	Pixel *pixel;
	for (int x = 0; x < width; ++x)
	{
		for(int y = 0; y < height; ++y)
		{
			pixel = image->pixels[x][y];
			if (pixel.r == 0 & pixel.g == 0 & pixel.b == 0)
			{
			}
			acc->value[x][y] = 1;
		}
	}
	return acc;
}


void houghTransform(Image* image)
{
	Matrix *acc = Constructor(image);
	printf("%d",acc->width);
	return;

}
