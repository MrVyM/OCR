#include <stdio.h>
#include <stdlib.h>
#include "../../include/Struct/pixel.h"
#include "../../include/Struct/image.h"
#include "../../include/Treatment/grayscale.h"
#include "../../include/Treatment/blur.h"
#include "../../include/Treatment/rotation.h"
#include "../../include/Treatment/hough.h"
#include "../../include/Treatment/square.h"
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
    square();
    freeImage(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}
