// Include
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Treatment/houghTransform.h"
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Treatment/rotation.h"
#include "Treatment/resize.h"

Image *extractSquare(Image *image, int x1, int y1, int x2, int y2)
{
    Image *square = createEmptyImage(x2 - x1, y2 - y1);
    for (int i = x1; i < x2; i++) // -> équivalent . mais en pointeur
    {
        for (int j = y1; j < y2; j++)
        {
            square->pixels[i-x1][j-y1] = image->pixels[i][j];
        }
    }
    return square;
}

int number(int *l)
{
    if (l[1] == 9999)
    {
        return 1;
    }
    // on fera appel au reseau de neurone
    return 0;
}

//version simple qui marche si le sudoku est seul
Image *findBiggest2(Image *image, Line **listeline){
	int i = 0;
    int x1 = image->width;
    int x2 = 0;
    int y1 = image->height;
    int y2 = 0;

    while(listeline[i] != 0){
        if (listeline[i]->x2 < image->width && listeline[i]->x2 > x2){
            x2 = listeline[i]->x2;
        }
        if (listeline[i]->y2 < image->height && listeline[i]->y2 > y2){
            y2 = listeline[i]->y2;
        }
        if (listeline[i]->x1 > 0 && listeline[i]->x1 < x1){
            x1 = listeline[i]->x1;
        }
        if (listeline[i]->y1 > 0 && listeline[i]->y1 < y1){
            y1 = listeline[i]->y1;
        }
        i++;
    }
    printf("x2 : %d\n",x2);
    printf("y2 : %d\n",y2);
    printf("x1 : %d\n",x1);
    printf("y1 : %d\n",y1);
    return extractSquare(image, x1, y1, x2, y2);
}


//version qui marche pas
Image *findbiggestSquare(Image *image, Line **listeline)
{

    int i = 0;
    int x = 0;
    int y = 0;
    int tempx = 0;
    int tempy = 0;

    // x1,y1,x2,y2 sont les coordonnée du plus grand carré trouvé
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

    // tempx1,y1,x2,y2 sont les coordonnée du carré en cours de recherche
    int tempx1 = 0;
    int tempy1 = 0;
    int tempx2 = 0;
    int tempy2 = 0;

    while (listeline[i] != 0)
    {
        x = listeline[i]->x1;
	printf("x : %d\n",x);
        y = listeline[i]->y1;
	printf("y : %d\n",y);
        int j = 0;
        // on cherche une ligne qui a un x proche de x

        while (listeline[j] != 0)
        {
            tempx = listeline[j]->x1;
            tempy = listeline[j]->y1;

            if (x == tempx)
            {
                tempx1 = x;
                // on regarde si c'est une ligne horizontale ou verticale
                if (listeline[i]->y1 < listeline[i]->y2)
                {

                    tempy1 = listeline[i]->y1;
                }
                else
                {
                    tempy1 = listeline[i]->y2;

                }
                if (listeline[j]->y1 < listeline[j]->y2)
                {
                    tempy2 = listeline[j]->y2;
                }
                else
                {
                    tempy2 = listeline[j]->y1;
                }
            }
            if (y == tempy)
            {
                tempy1 = y;
                // on regarde si c'est une ligne horizontale ou verticale
                if (listeline[i]->x1 < listeline[i]->x2)
                {
                    tempx1 = listeline[i]->x1;
                }
                else
                {
                    tempx1 = listeline[i]->x2;
                }
                if (listeline[j]->x1 < listeline[j]->x2)
                {
                    tempx2 = listeline[j]->x2;
                }
                else
                {
                    tempx2 = listeline[j]->x1;
                }
            }

            if (tempx1 > x1)
            {
	    	printf("tes un fils de pute : %d\n",tempx1);
                x1 = tempx1;
            }
            if (tempy1 > y1)
            {
                y1 = tempy1;
            }
            if (tempx2 > x2)
            {
                x2 = tempx2;
            }
            if (tempy2 > y2)
            {
                y2 = tempy2;
            }
	    j++;
        }
	i++;
    }
    printf("x fin : %d\n",x1);
    printf("y fin : %d\n",y1);
    return extractSquare(image, x1, y1, x2, y2);
}

// fonction qui découpe l'image en 9 carrés

Image **cutImage(Image *image)
{
    Image **tab = malloc(9 * sizeof(Image *));
    int x1, y1, x2, y2;
    int x = image->width / 3;
    int y = image->height / 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            x1 = i * x;
            y1 = j * y;
            x2 = (i + 1) * x;
            y2 = (j + 1) * y;
           tab[i * 3 + j] = extractSquare(image, x1, y1, x2, y2);
        }
    }
    return tab;
}

int *Imagetoint(Image *image)
{
    // on rezie l'image pour avoir une image de 28*28
    Image *image2 = resizeImage(image, 28*28);
    int *tab = malloc(28 * 28 * sizeof(int));
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            // on met 1 si le pixel est noir et 0 sinon
            if (image2->pixels[i][j].red == 0)
            {
                tab[i * 28 + j] = 1;
            }
            else
            {
                tab[i * 28 + j] = 0;
            }
        }
    }
    return tab;
}

int* createTab(Image **tab)
{
    // on crée un tableau de 9*9
    int* tab2 = malloc(sizeof(int) * 9);
    // on parcours le tableau d'image et on converti en tableau d'entier
    for (int i = 0; i < 9; i++)
    {

        //char s[25];
        //sprintf(s, "%d.%d tzt",i);
        //saveImage(tab[i],s); 
        tab2[i] = number(Imagetoint(tab[i]));
    }
    return tab2;
}

void decoupage(Image *image)
{
    // on découpe l'image en 9 carrés
    Image **tab = cutImage(image);
    // on crée un tableau de 9*9
    for (int i = 0;i <9;i++)
    {
        Image** subTab = cutImage(tab[i]);
        for(int j = 0; j < 9; j++)
        {
            char s[50];
            sprintf(s, "assets/Test/%d.%d.png",i,j);
            subTab[j] = resizeImage(subTab[j], 28);
            cleanImage(subTab[j]);
            saveImage(subTab[j],s); 
        }
	}
}

Image* traitement(Image *image, Line**listeline)
{
   int x1, y1, x2, y2;
   int i = 0;
   int x = image->width / 2;
    int y = image->height / 2;
   while(listeline[i] != 0){
         if(listeline[i]->x1 < x && listeline[i]->x2 < x){
              if(listeline[i]->y1 < y && listeline[i]->y2 < y){
                x1 = listeline[i]->x1;
                y1 = listeline[i]->y1;
                x2 = listeline[i]->x2;
                y2 = listeline[i]->y2;
              }
         }
         i++;
   }
    int longueur = sqrt(pow(x2-x1,2)+pow(y2-y1,2));
    int longueurOppose = sqrt(pow(x2-x1,2));
    double angle = asin(longueurOppose/longueur);
    printf("angle : %f\n",angle);
    Image *image2 = rotateImage(image,angle);
    return image2;
}

int **square(Image *image, Line **listeline)
{
    // int x1, y1, x2, y2;
    // findSquare(image, &x1, &y1, &x2, &y2);
    // Image *result= extractSquare(image, l[0], l[1], l[2], l[3]);
    //Image *image2= extractSquare(image,0,0,1011,128);
    //Image *image2 = findbiggestSquare(image, listeline);
    Image *image2 = traitement(image,listeline);
    Image *image3 = findBiggest2(image2,listeline);
    saveImage(image3, "square.bmp");
    decoupage(image3);
    return NULL;
}
