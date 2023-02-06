#ifndef FFT_H
#define FFT_H

#define bool int
#define true 1
#define false 0

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "stdlib.h"
#include "math.h"

struct Complex
{
    long double real, imag;
};
typedef struct Complex Complex;
Complex makeComplex(long double _real, long double _imag);
Complex addComplex(Complex a, Complex b);
Complex subComplex(Complex a, Complex b);
Complex multComplex(Complex a, Complex b);

void subblockSort(unsigned int n, Complex *arr);
void transform(unsigned int n, Complex *arr, bool inverseTransform);
int *multiplyPolynomials(unsigned int aSize, int *a, unsigned int bSize, int *b);

#endif