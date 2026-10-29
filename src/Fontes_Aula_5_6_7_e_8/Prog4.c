/*
 * ID: A05-08-P04
 * Aula: ../../atividades/aulas-05-e-06.md
 * Objetivo: Função Troca.
 */
/* Prog4.c */
/* Função Troca */
#include <stdio.h>
#include <stdlib.h>

void troca(int * , int *); /* protótipo */

int main(void)
{
    int v1, v2;

    printf("\nInsira o Primeiro Valor: ");
    if (scanf("%d", &v1) != 1) return 1;

    printf("\nInsira o Segundo Valor: ");
    if (scanf("%d", &v2) != 1) return 1;

    troca(&v1, &v2);

    printf("\nV1: %d; V2: %d", v1, v2);

    return 0;
}

/* Efetua a troca */
void troca(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

