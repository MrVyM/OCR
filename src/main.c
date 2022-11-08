#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
#include "Treatment/blur.h"
#include "Treatment/rotation.h"
#include "Treatment/hough.h"
#include "Treatment/square.h"
#include <err.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    }

    Image *image = importImage(argv[1]);
    //grayscaleImage(image);
    saveImage(image, "grayscale.bmp");
    //applyGaussianBlur(image);
    //houghTransform(image);
    //saveImage(image, "blur.bmp");
    //image = rotateImage(image, 25);
    //saveImage(image, "rotation.bmp");
    Image* image2 = square(image,houghTransform(image));
    saveImage(image2,"test.bmp");
    freeImage(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}
