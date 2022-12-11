#include <stdio.h>
#include <stdlib.h>
#include "Struct/pixel.h"
#include "Struct/image.h"
#include "Treatment/grayscale.h"
#include "Treatment/blur.h"
#include "Treatment/rotation.h"
#include "Treatment/resize.h"
#include "Treatment/thresolding.h"
#include "Treatment/sobel.h"
#include "Treatment/morph.h"
#include "Treatment/contrast.h"
#include "Treatment/gamma.h"
#include "Treatment/hough.h"
#include "Treatment/houghTransform.h"
#include <err.h>
#include "Struct/neuralNetwork.h"
#include "Struct/matrix.h"
#include "Xor/function.h"
#include "Input/file.h"
#include "Recognition/recognition.h"

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 3)
    {
        NeuralNetwork* net = loadWeight("h1.net","h2.net","ot.net");
        // printNeural(net);
        trainRecognition(net,sigmoid,deriv_sigmoid); 
        //printMatrix(net->output);
        saveWeight("h1.net","h2.net","ot.net",net);
    }
    else
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
            errx(EXIT_FAILURE, "%s", SDL_GetError());
        
        double angleRotation = 0;
        if (argc == 3)
            angleRotation = strtod(argv[2], NULL);

        printf("The image will be rotate with a angle of %.0f degrees.\n", angleRotation);
        Image *image = importImage(argv[1]);
        //image = resizeImage(image, 750);
        saveImage(image, "resize.bmp");
        grayscaleImage(image);
        saveImage(image, "grayscale.bmp");
        // Les tests ci-dessous sont des essais qui ont été non-concluants.
        // sobelOperator(image);
        // saveImage(image,"sobel.bmp");
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
        houghTransformBis(image);
        saveImage(image, "hough.bmp");
        image = rotateImage(image, angleRotation);
        saveImage(image, "rotation.bmp");
        freeImage(image);
        SDL_Quit();
    }
    return EXIT_SUCCESS;
}
