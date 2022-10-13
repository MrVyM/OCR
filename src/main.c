#include <stdio.h>
#include <stdlib.h>
#include "Struct/matrix.h"
#include "Xor/function.h"

int main(void)
{
    Matrix* m = initMatrix(2,2);
    Matrix* m1 = initMatrix(2,2);
    addScalarMatrix(m1,(float)(2));
    addScalarMatrix(m,(float)(1));
    mulScalarMatrix(m,(float)(2));
    addMatrix(m,m1);
    Matrix* m3 = mulMatrix(m,m1);
    printMatrix(m);
    printMatrix(m1);
    printMatrix(m3);
    freeMatrix(m);
    printf("%lf",sigmoid(0.2));
    return 0;
}
