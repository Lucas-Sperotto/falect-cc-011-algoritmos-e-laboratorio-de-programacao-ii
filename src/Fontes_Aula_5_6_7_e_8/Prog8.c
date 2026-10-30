/*
 * ID: A05-08-P08
 * Aula: ../../aulas/aula-06/README.md
 * Objetivo: Imprime os elementos de um vetor utilizando a notação de índices.
 */
/* Prog8.c */
/* Imprime os elementos de uma matriz usando notação matriz */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    static int M[5]= {92,81,70,69,58};
    int i;
    for(i=0; i<5; i++)
        printf("%d\n", M[i]); /* Notação matriz */

    // system("PAUSE");
    return 0;
}
