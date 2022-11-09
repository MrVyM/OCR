// Include
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/houghLines.h"
#include <stdio.h>

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

Line* findSquare(Line* listeline, int len){
    int xmin = 0;
    int xmax = 0;
    int ymin = 0;
    int ymax = 0;
    int i = 0;
    int size = len;
    while(size > i){
        if (listeline[i].x1 < xmin){
            xmin = listeline[i].x1;
        }
        if (listeline[i].x2 > xmax){
            xmax = listeline[i].x2;
        }
        if (listeline[i].y1 < ymin){
            ymin = listeline[i].y1;
        }
        if (listeline[i].y2 > ymax){
            ymax = listeline[i].y2;
        }
	i+=1;
    }
    //on cherche maintenant les 4 lignes
    Line result[3];
    i = 0;
    while(size > i){
        if (listeline[i].x1 == xmin && listeline[i].y1 == ymin){
            result[0] = listeline[i];
        }
        if (listeline[i].x1 == xmin && listeline[i].y2 == ymax){
            result[1] = listeline[i];
        }
        if (listeline[i].x2 == xmax && listeline[i].y1 == ymin){
            result[2] = listeline[i];
        }
        if (listeline[i].x2 == xmax && listeline[i].y2 == ymax){
            result[3] = listeline[i];
        }
	i += 1;
    }
    return result;

}
int* findSquare2(Line* listeline, int len){
    printf("here is findsquare\n");
    int xmin, xmax, ymin, ymax;
    int i = 0;
    printf("next\n");
    Line test = listeline[5];
    printf("stp marche\n");
    printf("ln : %d\n", test.x1);
    while(i<len){
        if (listeline[i].x1 < xmin){
            xmin = listeline[i].x1;
        }
        if (listeline[i].x2 > xmax){
            xmax = listeline[i].x2;
        }
        if (listeline[i].y1 < ymin){
            ymin = listeline[i].y1;
        }
        if (listeline[i].y2 > ymax){
            ymax = listeline[i].y2;
        }
	i+=1;
    }
    int* liste = malloc(sizeof(int)*4);
    liste[0] = xmin;
    liste[1] = xmax;
    liste[2] = ymin;
    liste[3] = ymax;
    return liste;
}

Image* square(Image* image,Line* listeline )
{
    printf("here dbut\n");
    //int x1, y1, x2, y2;
    //findSquare(image, &x1, &y1, &x2, &y2);
    int* l = findSquare2(listeline,5);
    printf("int %d\n",l[1]);
    Image *result= extractSquare(image, l[0], l[1], l[2], l[3]);
    //Image *result= extractSquare(image,50,50,200,200);
    return result;
}



