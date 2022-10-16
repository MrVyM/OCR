#include "Struct/image.h"
#include "Struct/pixel.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>

Image *createEmptyImage(int width, int height)
{
  Image *image = malloc(sizeof(Image));

    if (image == NULL)
        errx(-1, "Error while allocating a pointer (createEmptyImage)");
  
  image->width = width;
  image->height = height;
  image->pixels = calloc(width, sizeof(Pixel *));

  if (image->pixels == NULL)
    errx(-1, "Error while allocating a pointer (createEmptyImage)");

  for (int x = 0; x < width; x++)
  {
    image->pixels[x] = calloc(height, sizeof(Pixel *));
    if (image->pixels[x] == NULL)
      errx(-1, "Error while allocating a pointer (createEmptyImage)");
  }

  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
      image->pixels[x][y] = *initPixel(255, 255, 255);
  }

  return image;
}

Uint8 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
    Uint8 red, green, blue;
    SDL_GetRGB(pixel_color, format, &red, &green, &blue);
    return 0.3*red + 0.59*green + 0.11*blue;
}

Image *createImageFromSurface(SDL_Surface *surface)
{
  Image *image = createEmptyImage(surface->w, surface->h);
  Uint32* pixels = surface->pixels;
  SDL_PixelFormat* format = surface->format;

  if(SDL_LockSurface(surface) != 0)
    errx(EXIT_FAILURE, "%s", SDL_GetError());
  
  for(int x = 0; x < image->width; x++)
  {
    for(int y = 0; y < image->height; y++)
    {
      Pixel *pixel = &image->pixels[x][y];
      SDL_GetRGB(pixels[x * image->width + y], format, &pixel->red, &pixel->green, &pixel->blue);
    }
  }
  
  SDL_UnlockSurface(surface);
  return image;
}

void freeImage(Image *image)
{
  for(int x = 0; x < image->width; x++)
    free(image->pixels[x]);
  
  free(image->pixels);
  free(image);
}
