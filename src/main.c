#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"

int main(void)
{
    Pixel* test = initPixel(15,15,15);
    printPixel(test);
    updatePixelGrayColor(test, 27);
    printPixel(test);
    return 0;
}
