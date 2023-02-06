#include "fft.h"

Complex makeComplex(long double _real, long double _imag)
{
    Complex c;
    c.real = _real;
    c.imag = _imag;
    return c;
}

Complex addComplex(Complex a, Complex b)
{
    return makeComplex(a.real + b.real, a.imag + b.imag);
}

Complex subComplex(Complex a, Complex b)
{
    return makeComplex(a.real - b.real, a.imag - b.imag);
}

Complex multComplex(Complex a, Complex b)
{
    return makeComplex(a.real * b.real - a.imag * b.imag, a.real * b.imag + a.imag * b.real);
}

void subblockSort(unsigned int n, Complex *arr)
{
    // Sort elements by their original position's reversed bit order
    // e.g. for n equal to 8 sorted vector is a_0, a_4, a_2, a_6, a_1, a_5, a_3, a_7

    unsigned long int sortIndex = 0;
    unsigned long int reversedSortIndex = 0;

    while (sortIndex < n)
    {
        if (sortIndex < reversedSortIndex)
        {
            Complex t = arr[sortIndex];
            arr[sortIndex] = arr[reversedSortIndex];
            arr[reversedSortIndex] = t;
        }

        sortIndex++;

        // Increment reversedSortIndex by 1 to avoid recomputation
        unsigned long int bit = n >> 1;
        while (bit && (reversedSortIndex & bit))
            reversedSortIndex ^= bit, bit >>= 1;
        reversedSortIndex ^= bit;
    }
}

void transform(unsigned int n, Complex *arr, bool inverseTransform)
{
    subblockSort(n, arr);
    for (unsigned int blockSize = 2; blockSize <= n; blockSize <<= 1)
    {
        long double firstRootAngle = (long double)M_PI * 2 / blockSize;
        if (inverseTransform)
            firstRootAngle = -firstRootAngle;
        Complex firstRoot = makeComplex(cosl(firstRootAngle), sinl(firstRootAngle));
        unsigned int combinationOffset = blockSize >> 1;

        for (unsigned int blockBegin = 0; blockBegin + blockSize <= n; blockBegin += blockSize)
        {
            Complex currentRoot = makeComplex(1, 0);
            for (unsigned int root = 0; root < combinationOffset; ++root)
            {
                Complex a = arr[blockBegin + root];
                Complex b = multComplex(arr[blockBegin + root + combinationOffset], currentRoot);
                arr[blockBegin + root] = addComplex(a, b);
                arr[blockBegin + root + combinationOffset] = subComplex(a, b);
                currentRoot = multComplex(currentRoot, firstRoot);
            }
        }
    }

    if (inverseTransform)
        for (unsigned int i = 0; i < n; ++i)
        {
            arr[i].real /= n;
            arr[i].imag /= n;
        }
}

int *multiplyPolynomials(unsigned int aSize, int *a, unsigned int bSize, int *b)
{
    unsigned int cSize = aSize + bSize - 1;
    unsigned int size = 1;
    while (size < cSize)
        size <<= 1;

    Complex *complexA = malloc(sizeof(Complex) * size);
    Complex *complexB = malloc(sizeof(Complex) * size);
    Complex *complexC = malloc(sizeof(Complex) * size);

    for (unsigned int i = 0; i < size; ++i)
    {
        complexA[i] = makeComplex(0, 0);
        complexB[i] = makeComplex(0, 0);
        complexC[i] = makeComplex(0, 0);
    }

    for (unsigned int i = 0; i < aSize; ++i)
        complexA[i] = makeComplex(a[i], 0);
    for (unsigned int i = 0; i < bSize; ++i)
        complexB[i] = makeComplex(b[i], 0);

    transform(size, complexA, false);
    transform(size, complexB, false);
    for (unsigned int i = 0; i < size; ++i)
        complexC[i] = multComplex(complexA[i], complexB[i]);
    transform(size, complexC, true);

    int *c = malloc(sizeof(int) * cSize);
    for (unsigned int i = 0; i < cSize; ++i)
        c[i] = (int)(roundl(complexC[i].real));

    free(complexA);
    free(complexB);
    free(complexC);
    return c;
}
