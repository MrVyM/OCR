#include <stdio.h>
#include "Struct/matrix.h"

int main(void)
{
    Matrix* m = initMatrix(2,2);
    addScalarMatrix(m,(float)(1));
    mulScalarMatrix(m,(float)(2));
    printMatrix(m);

    freeMatrix(m);
    return 0;
}
