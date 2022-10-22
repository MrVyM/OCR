#ifndef LINE_H
#define LINE_H

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

Line initHoughLine(double theta, double r, int width, int height, int score);
void convertToCartesian(Line line);
#endif
