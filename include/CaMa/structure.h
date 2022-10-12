#pragma once

typedef struct 
{
    int length;
    char* value; 
} Vector;


struct Matrix
{
    int width;
    int height;
    char** value;
};

typedef struct Matrix Matrix;
