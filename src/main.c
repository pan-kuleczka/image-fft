#include <stdio.h>

#include "fft.h"

int main(int argc, char *argv[])
{
    int degA, degB;
    int *polyA, *polyB;

    printf(u8"Wpisz stopień pierwszego wielomianu: ");
    scanf("%d", &degA);
    ++degA;
    polyA = malloc(sizeof(int) * degA);
    printf(u8"Wpisz współczynniki pierwszego wielomianu: ");
    for (int i = degA - 1; i >= 0; --i)
        scanf("%d", polyA + i);

    printf(u8"Wpisz stopień drugiego wielomianu: ");
    scanf("%d", &degB);
    ++degB;
    polyB = malloc(sizeof(int) * degB);
    printf(u8"Wpisz współczynniki drugiego wielomianu: ");
    for (int i = degB - 1; i >= 0; --i)
        scanf("%d", polyB + i);

    int *polyC = multiplyPolynomials(degA, polyA, degB, polyB);
    printf(u8"Wynik to:\n");
    int anyPrinted = 0;
    for (int i = (degA + degB - 1) - 1; i >= 0; --i)
    {
        if (polyC[i] == 0)
            continue;

        if (polyC[i] > 0)
        {
            if (anyPrinted)
                printf(" + ");
        }
        else
            printf(" - ");

        printf("%dx**%d", abs(polyC[i]), i);
        anyPrinted = 1;
    }
    if (!anyPrinted)
        printf("0");
    printf("\n");

    free(polyA);
    free(polyB);
    free(polyC);
    return 0;
}