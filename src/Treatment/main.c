#include <stdio.h> 
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint8 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 red, green, blue;
    SDL_GetRGB(pixel_color, format, &red, &green, &blue);
    return 0.3*red + 0.59*green + 0.11*blue;
}

void surface_to_grayscale(SDL_Surface* surface, Uint8 * pixelsMatrix)
{
    Uint32* pixels = surface->pixels;
    size_t len = surface->w * surface->h;
    SDL_PixelFormat* format = surface->format;
    if(SDL_LockSurface(surface) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    for(size_t index = 0; index < len; index++)
        pixelsMatrix[index] = pixel_to_grayscale(pixels[index], format);
    SDL_UnlockSurface(surface);
}

void update_surface_pixels(SDL_Surface* surface, Uint8 * pixelsMatrix)
{
	Uint32* pixels = surface->pixels;
	size_t len = surface->w * surface->h;
	SDL_PixelFormat* format = surface->format;
	if(SDL_LockSurface(surface) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
	for(size_t index = 0; index < len; index++)
	{
		Uint8 color = pixelsMatrix[index];
		pixels[index] = SDL_MapRGB(format, color, color, color);
	}
	SDL_UnlockSurface(surface);
}

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

	size_t pixelsLen = surface->w * surface->h;
	Uint8 pixels[pixelsLen];
	surface_to_grayscale(surface, pixels);
	// TODO Traitement de l'image...
	update_surface_pixels(surface, pixels);

	if(SDL_SaveBMP(surface, "result_treatment.bmp") != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
	
    SDL_FreeSurface(surface);
    SDL_Quit();
	return EXIT_SUCCESS;
}
//gcc -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`   -c -o main.o main.c
//gcc   main.o  `pkg-config --libs sdl2 SDL2_image` -o main