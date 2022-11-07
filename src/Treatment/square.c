// Include
#include "../../include/Struct/image.h"
#include "../../include/Struct/pixel.h"
#include "../../include/Struct/houghLines.h"


Image* image = importImage("../../Assets/image_01.png");
Line listeline[] = houghTransform(image);


Image *extractSquare(Image *image, int x1, int y1, int x2, int y2)
{
    Image *square = createEmptyImage(x2 - x1, y2 - y1);
    for (int i = 0; i < square->height; i++) // -> équivalent . mais en pointeur
    {
        for (int j = 0; j < square->width; j++)
        {
            square->pixels[i][j] = image->pixels[i + y1][j + x1];
        }
    }
    return square;
}

Line findSquare(Line listeline[]){
    int xmin = 0;
    int xmax = 0;
    int ymin = 0;
    int ymax = 0;
    for(size_t i = 0; i < listeline.lenght;i++){
        if (listeline[i].x1 < xmin){
            xmin = listeline[i].x1
        }
        if (listeline[i].x2 > xmax){
            xmax = listeline[i].x2
        }
        if (listeline[i].y1 < ymin){
            ymin = listeline[i].y1
        }
        if (listeline[i].y2 > ymax){
            ymax = listeline[i].y2
        }
    }
    //on cherche maintenant les 4 lignes
    Line result[3];
    for(size_t i = 0; i < listeline.lenght;i++){
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
    }
    return result;

}



void main()
{
    //int x1, y1, x2, y2;
    //findSquare(image, &x1, &y1, &x2, &y2);
    Image *square = extractSquare(image, x1, y1, x2, y2);
    saveImage(square, "square.png");
}



