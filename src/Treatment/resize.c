#include "Struct/matrix.h"
#include "Struct/image.h"
#include <math.h>

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

Image *resizeImage(Image *image, int resizedValue)
{
    double ratio = 1;

    if (image->width > resizedValue || image->height > resizedValue)
        ratio = (double)resizedValue / min(image->width, image->height);

    if(ratio == 1)
        return image;
    
    int new_width = image->width * ratio;
    int new_height = image->height * ratio;
    Image *residedImage = createEmptyImage(new_width, new_height);

    for (int x = 0; x < new_width; x++)
    {
        for (int y = 0; y < new_height; y++)
            residedImage->pixels[x][y] = image->pixels[(int)(floor(x / ratio))][(int)(floor(y / ratio))];
    }
    free(image);
    return residedImage;
}