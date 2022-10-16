#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include <err.h>

int main(int argc, char** argv)
{
	// Checks the number of arguments.
    if (argc != 2)
        errx(EXIT_FAILURE, "Usage: image-file");

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	}
    
	SDL_Surface * surface = IMG_Load(argv[1]);
	if(surface == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());
	
    surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
	if(surface == NULL)
		errx(EXIT_FAILURE, "%s", SDL_GetError());

	Image *image = createImageFromSurface(surface);
    printPixel(&image->pixels[255][255]);
	
	
    SDL_FreeSurface(surface);
    SDL_Quit();
	return EXIT_SUCCESS;
}