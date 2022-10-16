#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
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
    grayscaleImage(image);
    saveImage(image, "test.bmp");
    freeImage(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}