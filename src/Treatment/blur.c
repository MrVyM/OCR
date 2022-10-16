#include <stdio.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define SIGMA 10
#define SIGMA2 SIGMA *SIGMA
#define TWO_PI 6.28318530718

// SOURCE : https://www.pixelstech.net/article/1353768112-Gaussian-Blur-Algorithm

double twoDimensionalGaussian(int x, int y)
{
    return 1 / (TWO_PI * SIGMA2) * exp(-(x * x + y * y) / (2 * SIGMA2));
}

void applyFilter(Uint8 *inPixels, Uint8 *outPixels, size_t rowPixels,
                 size_t pixelsSize, float *filterMatrix, size_t filterBorderSize)
{
    size_t radius = filterBorderSize / 2;
    size_t x;
    size_t y;
    for (size_t index = 0; index < pixelsSize; index++)
    {
        x = index % rowPixels;
        y = index / rowPixels;
        float sum = 0;

        for (size_t square_i = max(x - radius, 0); square_i < min(x + radius + 1, rowPixels); square_i++)
        {
            for (size_t square_j = max((int)y - (int)radius, 0); square_j < min(y + radius + 1, pixelsSize / rowPixels); square_j++)
            {
                ssize_t xFilter = ((ssize_t)square_i - (ssize_t)x + (ssize_t)radius);
                ssize_t yFilter = (ssize_t)square_j - (ssize_t)y + (ssize_t)radius;
                sum += inPixels[square_j * rowPixels + square_i] * filterMatrix[xFilter * filterBorderSize + yFilter];
            }
        }
        outPixels[index] = (Uint8)sum;
    }
}

void generateGaussianMatrix(int radius, float *gaussianMatrix)
{
    size_t borderSize = 2 * radius + 1;
    size_t matrixSize = borderSize * borderSize;
    float sumValues = 0;

    for (size_t index = 0; index < matrixSize; index++)
    {
        gaussianMatrix[index] = twoDimensionalGaussian(index / borderSize - radius, index % borderSize - radius);
        sumValues += gaussianMatrix[index];
    }

    for (size_t index = 0; index < matrixSize; index++)
        gaussianMatrix[index] /= sumValues;
}

/*void printMatrix(float* squaredMatrix, size_t borderSize)
{
    for(size_t index = 0; index < borderSize * borderSize; index++)
    {
        printf("%f ", squaredMatrix[index]);
        if(index % borderSize == borderSize - 1)
            printf("\n");
    }
}
*/