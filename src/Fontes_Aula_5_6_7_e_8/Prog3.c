/* Prog3.c */
/* Função Troca */
#include <stdio.h>
#include <stdlib.h>

void troca(int, int); /* protótipo */

int main()
{
    int v1, v2;

    printf("\nInsira o Primeiro Valor: ");
    scanf("%d", &v1);

    printf("\nInsira o Segundo Valor: ");
    scanf("%d", &v2);

    troca(v1, v2);

    printf("\nV1: %d; V2: %d", v1, v2);

    return 0;
}

/* Efetua a troca */
void troca(int x, int y)
{
    int temp;
    temp = x;
    x = y;
    y = temp;
}

