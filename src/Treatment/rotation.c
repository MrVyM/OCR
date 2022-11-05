#include "Struct/matrix.h"
#include "Struct/image.h"
#include <math.h>

// https://stackoverflow.com/questions/65554301/how-to-calculate-the-sizes-of-a-rectangle-that-contains-rotated-image-potential
void calculate_size(int a, int b, double theta, int *width, int *height)
{
    double diag = hypot(a, b) / 2;
    double theta0 = atan2(b, a);
    *width = 2 * diag * fmax(fabs(cos(theta + theta0)), fabs(cos(theta - theta0)));
    *height = 2 * diag * fmax(fabs(sin(theta + theta0)), fabs(sin(theta - theta0)));
}

Image *rotateImage(Image *image, double angle)
{
    if(angle == 0) return image;

    angle = angle *  M_PI / 180;

    int new_width, new_height;
    calculate_size(image->width, image->height, angle, &new_width, &new_height);

    Image *rotatedImage =  createEmptyImage(new_width, new_height);
    int center_x = rotatedImage->width / 2;
    int center_y = rotatedImage->height / 2;

    for(int x = 0; x < new_width; x++)
    {
        for(int y = 0; y < new_height; y++)
        {
            int xp = (x - center_x) * cos(angle) + (y - center_y) * sin(angle) + image->width/2;
            int yp = -(x - center_x) * sin(angle) + (y - center_y) * cos(angle) + image->height/2;
            if(0 <= xp && xp < image->width && 0 <= yp  && yp < image->height)
                rotatedImage->pixels[x][y] = image->pixels[xp][yp];
        }
    }
    free(image);
    return rotatedImage;
}