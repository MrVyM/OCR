#ifndef LINE_H
#define LINE_H

#include "Struct/image.h"

struct Line
{
	double theta;
	double r;
	double score;
	int x1;
	int y1;
	int x2;
	int y2;
};
typedef struct Line Line;

Line initHoughLine(double theta, double r, int score);
void convertToCartesian(Line line, int width, int height);
void drawHoughLine(Line line, int width, int height, Image *image);
void drawAndConvert(Line line, int width, int height, Image* image);
void draw_line(Image* image, int w, int h, Line line, int thickness, int draw);
#endif
