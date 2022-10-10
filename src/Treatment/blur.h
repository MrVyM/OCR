#ifndef BLUR_H
#define BLUR_H

double twoDimensionalGaussian(int x, int y);
void applyFilter(Uint8* inPixels, Uint8* outPixels, size_t rowPixels,
size_t pixelsSize, float* filterMatrix, size_t filterBorderSize);
void generateGaussianMatrix(int radius, float* gaussianMatrix);
void printMatrix(float* squaredMatrixe, size_t borderSize);

#endif