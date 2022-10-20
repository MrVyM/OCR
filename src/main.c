#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
#include "Treatment/blur.h"
#include "Treatment/rotation.h"
#include "Treatment/resize.h"
#include "Treatment/thresolding.h"
#include <err.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    Image *image = importImage(argv[1]);
    image = resizeImage(image);
    grayscaleImage(image);
    saveImage(image, "grayscale.bmp");
    /*applyGaussianBlur(image);
    saveImage(image, "blur.bmp");*/
    otsuTresolding(image);
    saveImage(image, "thresolding.bmp");
    image = rotateImage(image, 15);
    saveImage(image, "rotation.bmp");
    freeImage(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}