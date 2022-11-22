// 3 étapes:
// - Pour chaque point de contour détécté, détermination de la courbe
// - Construction de l'accumulateur (les maxima locaux de cette matrice correspondant à des droites probables)
// - Detection des pics dans l'accumulateur

#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include "Struct/houghLines.h"
#include "Struct/linesArray.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#define maxTheta 180

void swap(Line xp, Line yp)
{
	Line temp = xp;
	xp = yp;
	yp = temp;
}

LineArray topScoring(LineArray lines, int resize)
{
	LineArray line = initLinesArray(lines.index + 1);
	int min_idx;
	for (int i = 0; i < lines.index; ++i)
	{
		min_idx = i;
		for (int j = i + 1; j < lines.index + 1; ++j)
		{
			if (lines.value[j].score < lines.value[min_idx].score)
			{
				min_idx = j;
			}
		}
		if (min_idx != i)
			swap(lines.value[min_idx], lines.value[i]);
	}

	for (int i = 0; i < resize; ++i)
	{
		line.value[i] = lines.value[resize - i - 1];
		// printf("| value = %f |\n", line[i].score);
	}
	return line;
}

// Recherche des maximum de l'accumulateur
int findMaximum(int neighbourRadius, int t, int r, Matrix *acc, int peak)
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
				return 0;
			}
		}
	}
	return 1;
}

// Construction de l'accumulateur

LineArray Constructor(Image *image)
{

	int width = image->width;
	int height = image->height;

	// Hauteur maximale de l'accumulateur

	double diagonal = sqrt(height * height + width * width);
	int doubleHoughHeight = 2 * diagonal;
	Matrix *acc = initMatrix(maxTheta, diagonal);

	// Les coordonées du centre de l'image
	float centerX = width / 2;
	float centerY = height / 2;

	// Count le nombre de points remarquables
	long int numPoints = 0;

	double *sinArray = malloc(sizeof(double) * maxTheta);
	double *cosArray = malloc(sizeof(double) * maxTheta);

	// Le pas de theta
	double Theta = M_PI / maxTheta;
	// double Theta = maxTheta / doubleHoughHeight;
	for (int t = 0; t < maxTheta; ++t)
	{
		double realTheta = t * Theta;
		sinArray[t] = sin(realTheta);
		cosArray[t] = cos(realTheta);
	}

	unsigned int max = 0;
	// Add points
	// In the same time, we search for the max value in the accumulator

	Pixel *pixel;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			pixel = &image->pixels[x][y];
			if (pixel->red == 255)
			{
				// Ajout d'un point remarquable

				// Parcours tous les Theta compris entre 0 et 180
				for (int t = 0; t < maxTheta; t++)
				{

					// Calcul de rho pour chaque theta
					long int r = (int)(((x - centerX) * cosArray[t]) + ((y - centerY) * sinArray[t]));
					// long int r = (int)((x * cosArray[t]) + (y * sinArray[t]));

					// long int r = (int)( (x * cosArray[t] + y * sinArray[t]));
					//  r peut être négatif
					r += diagonal;
					if (r < 0 || r >= doubleHoughHeight)
					{
						break;
					}
					acc->value[t][r]++;
					if (acc->value[t][r] > max)
					{
						max = acc->value[t][r];
						//printf("t %d r %d \n", t, r);
					}
					// printf("acc value t = %d et r = %ld : %f \n", t, r, acc->value[t][r]);
					numPoints++;
				}
				// numPoints ++;
			}
		}
	}

	// LIBEREZ MEMOIRE
	free(cosArray);
	free(sinArray);
	// Extraire les lignes de l'accumulateur
	// printf("HERE\n");
	// Le seuil pour les maximums locaux

	// double threshold = 0;
	double threshold = width/2;
	//printf("max = %d \n threshold = %f\n", max, threshold);

	// Pointeur contenant les hough lines
	// printf("%ld", numPoints);
	LineArray lineArray = initLinesArray(numPoints + 1);

	//	printf("%f",acc->value[90][216]);
	//	drawAndConvert(initHoughLine(90, 216, acc->value[90][216]), width, height, image);

	if (numPoints == 0)
		return lineArray;

	// Recherche des maximums locaux
	for (int t = 0; t < maxTheta; ++t)
	{
		// printf("1t = %d |\n", t);
		//  Le nombre de voisin qu'on va comparer pour trouver le maximum local
		int neighbourRadius = 4;

		for (int r = neighbourRadius; r < doubleHoughHeight - neighbourRadius; ++r)
		{
			// Seulement les valeurs en dessous du seuil
			if (acc->value[t][r] > threshold)
			{
				// printf("val = %f \n", acc->value[t][r]);
				//  Initialisation de la valeur max
				int peak = (int)acc->value[t][r];
				// printf("%d\n", peak);

				if (findMaximum(neighbourRadius, t, r, acc, peak))
				{
					// Calcule de la bonne valeur de theta
					double realTheta = (t)*Theta;
					// Ajoute la line au pointeur
					//
					// printf("| value = %d |\n", lineArray.index);
					lineArray = appendLinesValue(initHoughLine(realTheta, r, (acc)->value[t][r]), lineArray);
				}
			}
		}
	}

	int resize = 30;
	LineArray lines = topScoring(lineArray, resize);
	// Calcul de chaque point en cartésien
	// printf("index = %d length = %d\n", lineArray.index,lineArray.length);
	for (int i = 0; i < resize; ++i)
	{
		// convertToCartesian(lines[i],width,height);
		// x1 = %d et y1 = %d\nx2 = %d et y2 =%d\n
		//, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2
		// printf("rho = %f theta = %f score = %f\n",lines[i].r,lines[i].theta, line[i].score);
		drawAndConvert(lines.value[i], width, height, image);
		// drawHoughLine(lines.value[i], width, height, image);
	}
	// free(line);
	saveImage(image, "hough.bmp");
	free(acc);
	return lineArray;
}

LineArray houghTransform(Image *image)
{
	LineArray lines = Constructor(image);
	return lines;
}
