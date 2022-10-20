#include "Treatment/thresolding.h"
#include "Struct/pixel.h"
#include "stdio.h"

// https://www.youtube.com/watch?v=jUUkMaNuHP8

void *generateHistogram(Image *image, int histogram[])
{
    for (int x = 0; x < image->width; x++)
    {
        for (int y = 0; y < image->height; y++)
            histogram[image->pixels[x][y].red] += 1;
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
            if (image->pixels[x][y].red < thresold/1.05)
                updateSameColorPixel(&image->pixels[x][y], 0);
            else
                updateSameColorPixel(&image->pixels[x][y], 255);
        }
    }
}

double computeOtsuVariance(int histogram[], Image *image, int thresold)
{
    double wb = 0, wf = 0, mb = 0, mf = 0;
    int totalPixels = image->width * image->height;

    for (int counter = 0; counter < 256; counter++)
    {
        if (counter < thresold)
        {
            wb += histogram[counter];
            mb += counter * histogram[counter];
        }
        else
        {
            wf += histogram[counter];
            mf += counter * histogram[counter];
        }
    }
    mb = wb != 0 ? mb / wb : 0;
    mf = wf != 0 ? mf / wf : 0;
    wb /= totalPixels;
    wf /= totalPixels;
    return wb * wf * (mb - mf) * (mb - mf);
}

int findThresholdOtsu(int histogram[], Image *image)
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
    int histogram[256] = {0};
    generateHistogram(image, histogram);
    applyThresolding(image, findThresholdOtsu(histogram, image));
}