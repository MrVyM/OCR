// 3 étapes:
// - Pour chaque point de contour détécté, détermination de la courbe
// - Construction de l'accumulateur (les maxima locaux de cette matrice correspondant à des droites probables)
// - Detection des pics dans l'accumulateur

// Include
#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include "Struct/houghLines.h"
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

	// Hauteur maximale de l'accumulateur (Varaible)
	int houghHeight;
	if (height > width)
		houghHeight = (int) (sqrt(2) * height) / 2;
	else
		houghHeight = (int) (sqrt(2) * width) / 2;

	// Le double de la hauteur (Stable)
	int doubleHoughHeight = houghHeight * 2;

	// Création de l'accumulateur
	Matrix * acc = initMatrix(maxTheta,height*2);
	
	// Les coordonées du centre de l'image
	int centerX = width / 2;
	int centerY = height / 2;

	// Count le nombre de points remarquables
	int numPoints = 0;

	int *sinArray = malloc(sizeof(int) * maxTheta);
	int *cosArray = malloc(sizeof(int) * maxTheta);

	// Le pas de theta
	int Theta = M_PI / maxTheta;

	for (int i = 0; i < maxTheta; ++i)
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
			pixel = &image->pixels[x][y];
			if (pixel->red == 0 & pixel->green == 0 & pixel->blue == 0)
			{
				// Ajout d'un point remarquable
				
				// Parcours tous les Theta compris entre 0 et 180
				for (int t = 0; t < maxTheta; t++)
				{
					// Calcul de rho pour chaque theta
					int r = (int)(((x - centerX) * cosArray[t]) + ((y - centerY) * sinArray[t]));

					// r peut être négatif
					r += houghHeight;

					if(!(r < 0 || r >= doubleHoughHeight))
					{
						acc->value[x][y]++;
					}
				}
				numPoints ++;

			}

		}
	}

	// LIBEREZ MEMOIRE

	// Extraire les lignes de l'accumulateur

	//
	Line* line = initHoughLine(Theta, 10, width, height, 0);

	if (numPoints == 0)

		//return line;
		return acc;
	return acc;
}


void houghTransform(Image* image)
{

	Matrix* acc = Constructor(image);
	int width = image->width;
	int height = image->height;
	// Les coordonées du centre de l'image
	int centerX = width / 2;
	int centerY = height / 2;

	for (int x = 0; x < width; ++x)
	{
		for(int y = 0; y < height; ++y)
		{
			printf("%f", acc->value[x][y]);
		}
	}
	
	printf("%d",acc->width);
	return;

}
