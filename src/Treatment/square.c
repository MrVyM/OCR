// Include
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Treatment/houghTransform.h"
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Struct/resize.h"

Image *extractSquare(Image *image, int x1, int y1, int x2, int y2)
{
    Image *square = createEmptyImage(x2 - x1, y2 - y1);
    for (int i = 0; i < x2-x1; i++) // -> équivalent . mais en pointeur
    {
        for (int j = 0; j < y2-y1; j++)
        {
            square->pixels[i][j] = image->pixels[i + y1][j + x1];
        }
    }
    return square;
}

int number(int* l){
	if(l[1] == 9999){
		return 1;
	}
	//on fera appel au reseau de neurone
	return 0;
}



/*
    fonction pour trouver le plus grand carré depuis une liste de ligne
*/

Image* findbiggestSquare(Image* image,Line** listeline){
    // on parcours la liste de ligne et on cherche le plus grand carré  
    // lorsqu'on a le x1,y1,x2,y2 on extrait le carré
    // on renvoie le carré

    int x1,y1,x2,y2;
    int x1max,y1max,x2max,y2max;
    int max = 0;
    int tmp;
    for(int i = 0; i < 5; i++){
        x1 = listeline[i]->x1;
        y1 = listeline[i]->y1;
        x2 = listeline[i]->x2;
        y2 = listeline[i]->y2;
        tmp = (x2-x1)*(y2-y1);
        if(tmp > max){
            max = tmp;
            x1max = x1;
            y1max = y1;
            x2max = x2;
            y2max = y2;
        }
    }
    Image* image2 = extractSquare(image, x1max,y1max, x2max, y2max);
    return image2;
}

// fonction qui découpe l'image en 9 carrés

Image** cutImage(Image* image){
    Image** tab = malloc(9*sizeof(Image*));
    int x1,y1,x2,y2;
    int x = image->width/3;
    int y = image->height/3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            x1 = i*x;
            y1 = j*y;
            x2 = (i+1)*x;
            y2 = (j+1)*y;
            tab[i*3+j] = extractSquare(image, x1,y1, x2, y2);
        }
    }
    return tab;
}

int* Imagetoint(Image* image){
    //on rezie l'image pour avoir une image de 28*28
    Image* image2 = resize(image,28,28);
    int* tab = malloc(28*28*sizeof(int));
    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            // on met 1 si le pixel est noir et 0 sinon
            if(image2->pixels[i][j].red == 0){
                tab[i*28+j] = 1;
            }else{
                tab[i*28+j] = 0;
            }
        }
    }
    return tab;
}

int** createTab(Image** tab){
    // on crée un tableau de 9*9
    int* tab2 = malloc(9*sizeof(int*));
    for(int i = 0; i < 9; i++){
        tab2[i] = malloc(9*sizeof(int));
    }
    // on parcours le tableau d'image et on converti en tableau d'entier
    for(int i = 0; i < 9; i++){
        tab2[i] = number(Imagetoint(tab[i]));
    }
    return tab2;
}

int** result(Image* image){
    // on découpe l'image en 9 carrés
    Image** tab = cutImage(image);
    // on crée un tableau de 9*9
    int** tab2 = createTab(tab);
    return tab2;
}



int** square(Image* image,Line** listeline )
{
    printf("here dbut\n");
    //int x1, y1, x2, y2;
    //findSquare(image, &x1, &y1, &x2, &y2);
    //Image *result= extractSquare(image, l[0], l[1], l[2], l[3]);
    //Image *result= extractSquare(image,50,50,200,200);
    Image* image2 = findbiggestSquare(image,listeline);
    saveImage(image2,"square.bmp");
    int** sudoku = result(image2);
    return sudoku;
}



