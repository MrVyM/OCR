#ifndef IMAGE_H
#define IMAGE_H

struct Pixel
{
	Uint8 red;
	Uint8 green;
	Uint8 blue;
};
typedef struct Pixel Pixel;

struct Image
{
	int width;
    int height;
    Pixel **pixels;
};
typedef struct Image Image;

void updatePixelGrayColor(Pixel* pixel, Uint8 color);
Image* createEmptyImage(int width, int height);
Image* createImageFromSurface(SDL_Surface* surface);
void saveImage(Image* image);
Image* cloneImage(Image* image);
void freeImage(Image* image);

#endif