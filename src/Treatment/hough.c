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

// Recherche des maximum de l'accumulateur
void findMaximum(int neighbourRadius, int t, int r, Matrix* acc, int peak)
{


	for (int x = -neighbourRadius; x <= neighbourRadius; ++x)
	{
		for (int y = -neighbourRadius; y <= neighbourRadius; ++y)
		{
			// Dérivée de theta
			int dt = t + x;

			// Dérivéé de rho
			int dr = r + y;

			if (dt < 0)
				dt += maxTheta;
			else if (dt >= maxTheta)
				dt -= maxTheta;
			if (acc->value[dt][dr] > peak)
			{
				break;
			}
		}
	}
}


// Construction de l'accumulateur

Line *Constructor(Image* image)
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
	
	// Le seuil pour les maximums locaux
	double threshold = 0.42;

	// Pointeur contenant les hough lines
	Line* lines = malloc(sizeof(Line) * 2000);
	int indexLine = 0;

	if (numPoints == 0)

		return lines;

	// Recherche des maximums locaux
	
	for (int t = 0; t < maxTheta; ++t)
	{
		// Le nombre de voisin qu'on va comparer pour trouver le maximum local
		int neighbourRadius = 4;

		for (int r = neighbourRadius; r < doubleHoughHeight - neighbourRadius; ++r)
		{
			// Seulement les valeurs en dessous du seuil
			if (acc->value[t][r] > threshold)
			{
				// Initialisation de la valeur max
				int peak = acc->value[t][r];

				findMaximum(neighbourRadius, t, r, acc, peak);

				// Calcule de la bonne valeur de theta
				double realTheta = t * Theta;

				// Ajoute la line au pointeur
				lines[indexLine] = initHoughLine(realTheta , r, width, height, acc->value[t][r]);
				indexLine += 1;
			}
		}
	}
	return lines;
}


void houghTransform(Image* image)
{
	Line* lines = Constructor(image);
	for (int i = 0; i < 2000; ++i)
	{
		printf("theta = %f; rho = %f; score = %f", lines[i].theta, lines[i].r, lines[i].score);
	}
	return;

}
