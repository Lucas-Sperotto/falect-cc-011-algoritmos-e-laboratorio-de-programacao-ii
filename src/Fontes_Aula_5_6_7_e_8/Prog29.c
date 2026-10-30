/*
 * ID: A05-08-P29
 * Aula: ../../aulas/aula-08/README.md
 * Objetivo: Mostra o uso de malloc() para alocação dinâmica de memória.
 */
/* Prog29.c */
/* mostra o uso de malloc() */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *pi;

    pi = malloc(sizeof *pi);
    if (pi == NULL) return 1;

    puts("Digite um número: ");
    if (scanf("%d", pi) != 1) { free(pi); return 1; }
    printf("\nVocê digitou o número %d\n", *pi);

    free(pi);

    // system("PAUSE");
    return 0;
}
