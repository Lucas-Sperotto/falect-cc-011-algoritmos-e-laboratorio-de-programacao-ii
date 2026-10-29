/*
 * ID: A05-08-P01
 * Aula: ../../atividades/aulas-05-e-06.md
 * Objetivo: Mostra ponteiros constantes.
 */
/* Prog1.c */
/* Mostra ponteiros constantes */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i,j,k;

    printf("Endereço de i = %p\n", (void *)&i); /* %p para ponteiros */
    printf("Endereço de j = %p\n", (void *)&j);
    printf("Endereço de k = %p\n", (void *)&k);

    // system("PAUSE");
    return 0;
}
