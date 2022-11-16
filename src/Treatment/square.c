// Include
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/houghLines.h"
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

int number(int l[]){
	//on fera appel au reseau de neurone
	return 0;
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

int[784] caseInt(Image* image){
	Image* newimage = resizeImage(image,28*28);
	int pixel = newsimage->pixels;
	int result[784];
	for (int i = 0; i <= 28; i++){
		for (int j = 0; j <= 28; j++){
			// recup couleur ??
			Uint8 color = get()
			if (color = (0,0,0)){ //black
				result[i*i + j] = 1;
			}
			else {
				result[i*i + j] = 0;
			}
		}
	}
	return result;
}


Image* Cut(Image* image){
	int width = image->width;
	int height = image->height;
	int pixel = image->pixels;
	
	int w = 0;
	int h = 0;
	int tempw = 0;
	int temph = 0;
	Image* listeCase[3][3];
	
	Image* img;
	for (int i = 1; i <= 3; i++){
		w = width* ((1/3)*(i-1));
		
		for (j = 1; j <= 3;j++){
			h = height* ((1/3)*(i-1));
			tempw = width*((1/3)*i);
			temph = height*((1/3)*i);
			img = extractSquare(image, w, tempw,h,temph);
			listeCase[i-1][j-1] = img;
		}
	}
	return listeCase;
}

int[9][9] result(Image* image){
	
	Image* listeimg = Cut(image);
	int res[9][9];
	int x = 1;
	int temp;
	for (int i = 0; i < 3;i++){
		for (int j = 0; j < 3; j++){
			Image* limg2 = Cut(listeimg[i][j]);
			for (int i2 = 0; i2 < 3; i2++){
				for (int j2 = 0; j2 < 3; j2++){
					temp = number(caseInt(limg2[i2][j2]));
					res[i2*x][j2*x] = temp;
				}
			}
			x += 1;
		}
	}
	return res;
}


int[9][9] square(Image* image,Line* listeline )
{
    printf("here dbut\n");
    //int x1, y1, x2, y2;
    //findSquare(image, &x1, &y1, &x2, &y2);
    int* l = findSquare2(listeline,5);
    printf("int %d\n",l[1]);
    //Image *result= extractSquare(image, l[0], l[1], l[2], l[3]);
    //Image *result= extractSquare(image,50,50,200,200);
    Image* image2 = extractSquare(image, l[0]. l[1], l[2], l[3]);
    int[9][9] sudoku = result(image2);
    return sudoku;
}



