#ifndef LINE_H
#define LINE_H

struct Line
{
	double theta;
	double r;
	double score;
};
typedef struct Line Line;

Line* initHoughLine(double theta, double r, int width, int height, int score);
void freeLine(Line* line);
#endif
