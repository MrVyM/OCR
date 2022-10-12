#include <stdio.h>
#include "Struct/matrix.h"

int main(void)
{
    Matrix* m = initMatrix(2,2);
    Matrix* m1 = initMatrix(2,2);
    addScalarMatrix(m1,(float)(2));
    addScalarMatrix(m,(float)(1));
    mulScalarMatrix(m,(float)(2));
    addMatrix(m,m1);
    printMatrix(m);

    freeMatrix(m);
    return 0;
}
