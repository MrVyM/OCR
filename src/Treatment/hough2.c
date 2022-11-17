#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include "Struct/houghLines.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#define maxTheta 180
#define minTheta 0


void swap(Line* xp, Line* yp)
{
	Line temp = *xp;
	*xp = *yp;
	*yp = temp;
}


