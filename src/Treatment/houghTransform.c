#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include "Struct/line.h"
#include <stdio.h>
#include <math.h>
#define MAX_THETA 360
#define STEP_THETA 0.5
#define THRESOLDING (max * 0.5)
double radiansToDegrees(double radians)
{
    return radians * 180.0 / M_PI;
}

double degreesToRadians(double degrees)
{
    return degrees * M_PI / 180.0;
}

Matrix *createAccumulator(Image *image)
{
    int max_rho = ceil(sqrt(image->width * image->width + image->height * image->height));
    Matrix *accumulator = initMatrix(MAX_THETA + 1, max_rho + 1);
    return accumulator;
}

Line **fillHoughMatrix(Image *image, Matrix *accumulator, int sobel_on, double thresold)
{
    int max = thresold == 0 ? 0 : (int) thresold;
    double cosList[MAX_THETA + 1], sinList[MAX_THETA + 1];
    for (int theta = 0; theta <= MAX_THETA; theta++)
    {
        cosList[theta] = cos(degreesToRadians(theta));
        sinList[theta] = sin(degreesToRadians(theta));
    }
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            if ((!sobel_on && image->pixels[x][y].red != 0)  || (sobel_on && image->pixels[x][y].red == 0))
                continue;
            for (int theta = 0; theta <= MAX_THETA; theta++)
            {
                int rho = x * cosList[theta] + y * sinList[theta];
                if (rho < 0)
                    continue;
                accumulator->value[rho][theta]++;
                if (accumulator->value[rho][theta] > max)
                    max = accumulator->value[rho][theta];
            }
        }
    }
    // Counts number of lines detected
    int linesNumber = 0;
    for (int x = 1; x < accumulator->width; x++)
    {
        for (int y = 0; y < accumulator->height; y++)
        {
            if (accumulator->value[x][y] >= (thresold != 0 ? max : (THRESOLDING)))
                linesNumber++;
        }
    }
    Line **lines = calloc(linesNumber + 1, sizeof(Line));
    lines[linesNumber] = NULL;
    linesNumber = 0;
    int diagonale = ceil(sqrt(image->width * image->width + image->height * image->height));
    for (int rho = 1; rho < accumulator->height; rho++)
    {
        for (int theta = 0; theta < accumulator->width; theta++)
        {
            if (accumulator->value[rho][theta] >= (thresold != 0 ? max : (THRESOLDING)))
            {
                double a = cosList[theta], b = sinList[theta];
                int x0 = rho * a, y0 = rho * b;
                int x1 = x0 + diagonale * (-b), y1 = y0 + diagonale * a;
                int x2 = x0 - diagonale * (-b), y2 = y0 - diagonale * a;
                lines[linesNumber] = initLine(theta, rho, accumulator->value[rho][theta], x1, y1, x2, y2);
                linesNumber++;
            }
        }
    }
    return lines;
}

Line** houghTransform(Image *image, int sobel_on, double thresold)
{
    Matrix *accumulator = createAccumulator(image);
    Line **lines = fillHoughMatrix(image, accumulator, sobel_on, thresold);
    for (int index = 0; lines[index] != NULL; index++)
        drawLine(image, lines[index]);
    free(accumulator);
    return lines;
}