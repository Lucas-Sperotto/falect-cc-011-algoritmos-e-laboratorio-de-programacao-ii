/*
 * ID: A05-08-P24
 * Aula: ../../aulas/aula-07/README.md
 * Objetivo: Mostra o uso de ponteiros genéricos com conversão de tipos.
 */
/* Prog24.c */
/* Mostra ponteiros void */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i=5, *pi;
    float f=3.2, *pf;

    void *pv;	/* Ponteiro genérico */
    pv = &i;	/* Endereço de um int */

    pi = (int *)pv; /* Convertendo o tipo do ponteiro */
    printf("%d\n", *pi); /* Correto */

    pv = &f;	/* Endereço de um float */

    pf = (float *) pv; /* Convertendo o tipo do ponteiro */
    printf("%f\n", *pf);/* Correto */

    // system("PAUSE");
    return 0;
}
