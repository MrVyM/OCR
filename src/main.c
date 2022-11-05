#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
#include "Treatment/blur.h"
#include "Treatment/rotation.h"
#include "Treatment/resize.h"
#include "Treatment/thresolding.h"
#include "Treatment/morph.h"
#include "Treatment/contrast.h"
#include "Treatment/gamma.h"
#include <err.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    Image *image = importImage(argv[1]);
    image = resizeImage(image, 750);
    saveImage(image, "resize.bmp");
    grayscaleImage(image);
    saveImage(image, "grayscale.bmp");
    // Les tests ci-dessous sont des essais qui ont été non-concluants.
    // applyGamma(image, 255);
    // saveImage(image, "gamma.bmp");
    // applyContrast(image, 128);
    // saveImage(image, "contrast.bmp");
    // applyGaussianBlur(image);
    // saveImage(image, "blur.bmp");
    // dilate(image, 5);
    // saveImage(image, "dilate.bmp");
    // erode(image, 5);
    // saveImage(image, "erode.bmp");
    otsuTresolding(image);
    saveImage(image, "thresolding.bmp");
    image = rotateImage(image, 15);
    saveImage(image, "rotation.bmp");
    freeImage(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}