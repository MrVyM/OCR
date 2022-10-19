#include "Treatment/thresolding.h"
#include "Struct/pixel.h"
#include "stdio.h"

// https://www.youtube.com/watch?v=jUUkMaNuHP8

Matrix *generateHistogram(Image *image)
{
    Matrix *histogram = initMatrix(1,256);
    size_t a = 0;
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            
            //printPixel(&image->pixels[x][y]);
            Pixel *pixel = &(image->pixels[x][y]);
            a = 0;
            a = pixel->blue;

            //printf("%zu\n ", a);
            if (a == 66)
            {
                printf("x : %5d | y : %5d\n ", x, y);
                printPixel(&(image->pixels[x][y]));
                float x = histogram->value[0][a] + 1.0;
                printf("\n%f -- ",x);
                histogram->value[0][a] = histogram->value[0][a] + 1.0;
            }
            //printMatrix(histogram);
        
            //histogram->value[0][a] = histogram->value[0][a] + (float)(1.0);
        }
    }

    /*printf("color,numbers\n");
    for(int index = 0; index < 256; index++)
        printf("%3d,%7d\n", index, (int) histogram->value[0][index]);*/

    return histogram;
}

void applyThresolding(Image *image, int thresold)
{
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
        {
            if (image->pixels[x][y].red < thresold)
                updateSameColorPixel(&image->pixels[x][y], 0);
            else
                updateSameColorPixel(&image->pixels[x][y], 255);
        }
    }
}

double computeOtsuVariance(Matrix *histogram, Image *image, int thresold)
{
    double wb = 0, wf = 0, mb = 0, mf = 0;
    int totalPixels = image->width * image->height;

    for (int counter = 0; counter < 256; counter++)
    {
        if (counter < thresold)
        {
            wb += histogram->value[0][counter];
            mb += counter * histogram->value[0][counter];
        }
        else
        {
            wf += histogram->value[0][counter];
            mf += counter * histogram->value[0][counter];
        }
    }
    mb = wb != 0 ? mb / wb : 0;
    mf = wf != 0 ? mf / wf : 0;
    wb /= totalPixels;
    wf /= totalPixels;
    return wb * wf * (mb - mf) * (mb - mf);
}

int findThresholdOtsu(Matrix *histogram, Image *image)
{
    double thresoldingMax = -1;
    int thresoldIntensityMax = -1;
    for (int thresoldIntensity = 0; thresoldIntensity < 256; thresoldIntensity++)
    {
        double computedValue = computeOtsuVariance(histogram, image, thresoldIntensity);
        if (computedValue > thresoldingMax)
        {
            thresoldingMax = computedValue;
            thresoldIntensityMax = thresoldIntensity;
        }
    }
    return thresoldIntensityMax;
}

void otsuTresolding(Image *image)
{
    Matrix *histogram = generateHistogram(image);
    applyThresolding(image, findThresholdOtsu(histogram, image));
    printMatrix(histogram);
    freeMatrix(histogram);
}