#include <stdio.h>
#include <math.h>
#include "Struct/image.h"
#include "Struct/filter.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#define SIGMA 10
#define SIGMA2 SIGMA *SIGMA
#define TWO_PI 6.28318530718

// SOURCE : https://www.pixelstech.net/article/1353768112-Gaussian-Blur-Algorithm

float twoDimensionalGaussian(int x, int y)
{
    return 1 / (TWO_PI * SIGMA2) * exp(-(x * x + y * y) / (2 * SIGMA2));
}

void applyGaussianBlur(Image *image)
{
    Filter *filter = createFilter(3, twoDimensionalGaussian, 1);
    applyFilter(filter, image);
    freeFilter(filter);
}