// Include
#include <stdlib.h>
#include "Struct/image.h"
#include "Struct/pixel.h"
#include "Struct/matrix.h"
#include "Struct/houghLines.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>
#include hough.c

/*
On va tout d'abord trouver l'intersection entre 2 lignes
On veut trouver le x et y min et le x et y max
*/
Image* image = importImage("../../Assets/image_01.png");
Line[] listeline = houghTransform(image);

//On crée une liste avec toute les intersections entre les lignes

int[] Allx(Line[] listeline){
    int[] listInter;
    for(int i = 0; i < listeline.length; i++){
        
        listInter[i] = listeline[i].x2-listeline[i].x1;
            
    }
    
    return listInter;
}

int[] Ally(Line[] listeline){
    int[] listInter;
    for(int i = 0; i < listeline.length; i++){
        
        listInter[i] = listeline[i].y2-listeline[i].y1;
            
    }
    
    return listInter;
}

int MaxX(int[] Allx){
    int max = Allx[0];
    for(int i = 0; i < Allx.length; i++){
        if(Allx[i] > max){
            max = Allx[i];
        }
    }
    return max;
}
int MinX(int[] Allx){
    int min = Allx[0];
    for(int i = 0; i < Allx.length; i++){
        if(Allx[i] < min){
            min = Allx[i];
        }
    }
    return min;
}

int MaxY(int[] Ally){
    int max = Ally[0];
    for(int i = 0; i < Ally.length; i++){
        if(Ally[i] > max){
            max = Ally[i];
        }
    }
    return max;
}

int MinY(int[] Ally){
    int min = Ally[0];
    for(int i = 0; i < Ally.length; i++){
        if(Ally[i] < min){
            min = Ally[i];
        }
    }
    return min;
}


