/*
 * ID: A05-08-P23
 * Aula: ../../aulas/aula-07/README.md
 * Objetivo: Mostra o uso e as limitações de ponteiros do tipo void.
 */
/* Prog23.c */
/* Mostra ponteiros void */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i=5;
    float f=3.2;

    void *pv;	/* Ponteiro genérico */
    pv = &i;	/* Endereço de um int */

    /* não podemos usar o operador indireto com ponteiros void */
    /* printf("%d\n", *pv); ERRO intencional: void não tem valor. */
    printf("%d\n", *(int *)pv); /* Converter antes de acessar, como em Prog24. */

    pv = &f;	/* Endereço de um float */

    /* não podemos usar o operador indireto com ponteiros void */
    /* printf("%f\n", *pv); ERRO intencional. */
    printf("%f\n", *(float *)pv);

    // system("PAUSE");
    return 0;
}

