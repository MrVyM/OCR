#include "../../include/Struct/matrix.h"
#include "../../include/Struct/image.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <err.h>

Image *rotateImage(Image *image, double angle)
{
    angle = angle *  M_PI / 180;
    printf("Angle : %f\n", angle * 180 / M_PI);
    int new_width, new_height;
    if(angle < M_PI)
    {
        new_width = image->width * cos(angle) + image->height * sin(angle);
        new_height = image->width * sin(angle) + image->height * cos(angle);
    }
    else
    {
        new_width = image->height * cos(angle-M_PI) + image->width * sin(angle-M_PI);
        new_height = image->height * sin(angle-M_PI) + image->width * cos(angle-M_PI);
    }
    printf("%d - %d", new_width, new_height);
    Image *rotatedImage =  createEmptyImage(new_width, new_height);

    for(int x = 0; x < image->width; x++)
    {
        for(int y = 0; y < image->height; y++)
        {
            int xValue = (int) (x * cos(angle) + y * sin(angle));
            xValue = xValue >= 0 ? xValue : 0;
            int yValue = (int) (-x * sin(angle) + y * cos(angle)) + new_height/2;
            yValue = yValue >= 0 ? yValue : 0;
            rotatedImage->pixels[xValue][yValue] = image->pixels[x][y];
        }
    }
    free(image);
    return rotatedImage;
}