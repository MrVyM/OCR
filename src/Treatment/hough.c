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


void swap(Line* xp, Line* yp)
{
	Line temp = *xp;
	*xp = *yp;
	*yp = temp;
}

Line *topScoring(Line* lines, int n, int len)
{
	Line* line = malloc(sizeof(Line) * n);
	int min_idx;
	for (int i = 0; i < len - 1; ++i)
	{
		min_idx = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (lines[j].score < lines[min_idx].score)
			{
				min_idx = j;
			}
		}
		if(min_idx != i)
			swap(&lines[min_idx], &lines[i]);
	}
	
	for (int i = 0; i < n; ++i)
	{
		line[i] = lines[n - i -1];
		printf("| value = %f |\n", line[i].score);
	}
	return line;
}


// Recherche des maximum de l'accumulateur
int findMaximum(int neighbourRadius, int t, int r, Matrix* acc, int peak)
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

Line *Constructor(Image* image)
{
	
	int width = image->width;
	int height = image->height;

	// Hauteur maximale de l'accumulateur
	double diagonal = sqrt(width * width + height * height);
	/*
	int diagonal;
	if (height > width)
		diagonal = (int)(sqrt(2) * height) / 2;
	else
		diagonal = (int)(sqrt(2) * width) / 2;
	*/
	double doubleHoughHeight = 2 * diagonal;
	Matrix* acc = initMatrix(maxTheta, doubleHoughHeight);

	// Les coordonées du centre de l'image
	int centerX = width / 2;
	int centerY = height / 2;

	// Count le nombre de points remarquables
	long int numPoints = 0;

	double *sinArray = malloc(sizeof(double) * maxTheta);
	double *cosArray = malloc(sizeof(double) * maxTheta);

	// Le pas de theta
	double Theta = M_PI / maxTheta;
	//double Theta = maxTheta / doubleHoughHeight;
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
	for (int x = 0; x < width; ++x)
	{
		for(int y = 0; y < height; ++y)
		{
			pixel = &image->pixels[x][y];
			if (pixel->red == 0 && pixel->blue == 0 && pixel->red == 0)
			{
				// Ajout d'un point remarquable
				
				// Parcours tous les Theta compris entre 0 et 180
				for (int t = 0; t < maxTheta; t++)
				{

					// Calcul de rho pour chaque theta
					//long int r = (int) (((x - centerX) * cosArray[t]) + ((y - centerY) * sinArray[t]));
					//long int r = (int)((x * cosArray[t]) + (y * sinArray[t]));

					long int r = (int)( (x * cosArray[t] + y * sinArray[t]));
					// r peut être négatif
					//r += diagonal;
					if(r < 0 || r >= diagonal)
					{
						
						break;
					}

					acc->value[t][r]++;
					if (acc->value[t][r] > max)
					{
						max = acc->value[t][r];
					}
					//printf("acc value t = %d et r = %ld : %f \n", t, r, acc->value[t][r]);
				}
				numPoints ++;
			}

		}
	}

	// LIBEREZ MEMOIRE
	free(cosArray);
	free(sinArray);
	// Extraire les lignes de l'accumulateur
	//printf("HERE\n");
	// Le seuil pour les maximums locaux
	
	
	//double threshold = 0;
	double threshold = 0.7 * max;
	//printf("max = %d \n threshold = %f\n", max, threshold);

	// Pointeur contenant les hough lines
	//printf("%ld", numPoints);
	Line* lines = malloc(sizeof(Line) * numPoints);

	int indexLine = 0;

	if (numPoints == 0)
		return lines;

	for (int t = 0; t < maxTheta; ++t)
	{
		for (int r = 0; r < (int)(diagonal * 2); ++r)
		{
			if (acc->value[t][r] > threshold)
			{
				//printf("ALED t %d r %d\n",t,r);
				double realTheta = t * Theta;
				lines[indexLine] = initHoughLine(realTheta, r, acc->value[t][r]);
				indexLine += 1;
			}
		}
	}

	/*
	// Recherche des maximums locaux
	for (int t = 0; t < maxTheta; ++t)
	{
		//printf("1t = %d |\n", t);
		// Le nombre de voisin qu'on va comparer pour trouver le maximum local
		int neighbourRadius = 4;

		for (int r = neighbourRadius; r < doubleHoughHeight - neighbourRadius; ++r)
		{
			//printf("2t = %d |\n", t);
			// Seulement les valeurs en dessous du seuil
			if (acc->value[t][r] > threshold)
			{
				//printf("val = %f \n", acc->value[t][r]);
				// Initialisation de la valeur max
				int peak = (int) acc->value[t][r];
				printf("%d\n", peak);
				
				if (findMaximum(neighbourRadius, t, r, acc, peak))
				{
					// Calcule de la bonne valeur de theta
					double realTheta = t * Theta;
					// Ajoute la line au pointeur
					//
					//printf("| value = %f |\n", acc->value[t][r]);
					lines[indexLine] = initHoughLine(realTheta, r, acc->value[t][r]);
					indexLine += 1;
				}
				/*
				double realTheta = t * Theta;
				// Ajoute la line au pointeur
				//
				//printf("| value = %f |\n", acc->value[t][r]);
				lines[indexLine] = initHoughLine(realTheta, r, acc->value[t][r]);
				indexLine += 1;
				
			}
		}
	}*/
	//int resize = 12;
	//Line *line = topScoring(lines, resize, indexLine);
	// Calcul de chaque point en cartésien
	for (int i = 0; i < indexLine; ++i)
	{
		//convertToCartesian(lines[i],width,height);
		//x1 = %d et y1 = %d\nx2 = %d et y2 =%d\n
		//, lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2
		//printf("rho = %f theta = %f score = %f\n",lines[i].r,lines[i].theta, line[i].score);
		drawAndConvert(lines[i], width, height, image);
		//drawHoughLine(lines[i], width, height, image);
	}
	//free(line);
	saveImage(image, "hough.bpm");
	free(lines);
	return lines;
	
}

void houghTransform(Image* image)
{
	Line* lines = Constructor(image);
	return;

}
