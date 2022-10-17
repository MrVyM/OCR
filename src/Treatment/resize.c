#include "Struct/matrix.h"
#include "Struct/image.h"
#include <math.h>

Image *resizeImage(Image *image)
{
    double ratio = 0.5;
    int new_width =  image->width * ratio;
    int new_height = image->height * ratio;
    double x_scale = image->width / new_width;
    double y_scale = image->height / new_height;
    Image *residedImage = createEmptyImage(new_width, new_height);

    for(int x = 0; x < new_width; x++)
    {
        for(int y = 0; y < new_height; y++)
            residedImage->pixels[x][y] = image->pixels[(int)floor(x * x_scale)][(int)floor(y * y_scale)];
    }
    free(image);
    return residedImage;
}