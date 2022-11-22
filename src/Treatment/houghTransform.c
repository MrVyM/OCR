#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include <stdio.h>
#include <math.h>

#define MAX_THETA 180
#define STEP_THETA 1
#define STEP_2_THETA 2

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
    Matrix *accumulator = initMatrix(MAX_THETA + 1,max_rho +1);
    printf("Accumulateur : max_rho : %5d | max_theta : %5d\n", accumulator->width, accumulator->height);
    printf("Accumulateur : max_rho : %5d | max_theta : %5d\n", max_rho, MAX_THETA);
    //printf("Accumulateur %f\n",accumulator->value[max_rho][MAX_THETA]);
    return accumulator;
}

Matrix *fillHoughMatrix(Image *image, Matrix *accumulator)
{
    size_t max_rho = 0;
    size_t max_theta = 0;
    printf("%d, %d\n", accumulator->width, accumulator->height);
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            if (image->pixels[x][y].red != 0)
                continue;
            for (double theta = 0; theta <= MAX_THETA; theta++)
            {
                int rho = x * cos(degreesToRadians(theta)) + y * sin(degreesToRadians(theta));
                if(rho < 0) continue;
                if(rho > max_rho) max_rho = rho;
                if(theta > max_theta) max_theta = theta;
                //printf("X : %5d | Y : %5d | RHO : %5d | THETA : %5f\n", x, y, rho, theta);
                
            
                printf("%f\n", accumulator->value[rho][(int) theta]);
                    
            }
        }
    }
    printf("%zu | %zu\n", max_rho, max_theta / STEP_THETA);

    // Find lines by iterating the accumulator
    for (int x = 0; x < accumulator->width; x++)
    {
        for (int y = 0; y < accumulator->height; y++)
        {
            if (accumulator->value[x][y] < image->width / 2)
                continue;
            printf("Line found : %5d | %5d\n", x, y);
        }
    }
    return accumulator;
}

void houghTransformBis(Image *image)
{
    Matrix *accumulator = createAccumulator(image);
    fillHoughMatrix(image, accumulator);
    free(accumulator);
}