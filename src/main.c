#include <stdio.h>

#include "fft.h"

int main(int argc, char *argv[])
{
    printf("Hello, world!\n");

    int polyA[] = {1, 2, 3};
    int polyB[] = {1, 2, 3};
    int *polyC = multiplyPolynomials(3, polyA, 3, polyB);
    printf("%d\n", polyC[2]);
    return 0;
}