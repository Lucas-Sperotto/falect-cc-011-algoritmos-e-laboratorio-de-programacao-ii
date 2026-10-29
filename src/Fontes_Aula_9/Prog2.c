/*
 * ID: A09-P02
 * Aula: ../../aulas/aula-09.md
 * Objetivo: todos os bits ligados
 */
/* Prog2.c */
#include <stdio.h>
#include <stdlib.h>

int palavra(void)
{
    unsigned int n = ~0; /* todos os bits ligados */
    int i;
    for(i = 0; n ; i++) /* enquanto n não for zero */
        n <<= 1;
    return i;
}

int main(void)
{
    int t = palavra();
    printf("O tamanho de unsigned int nessa máquina é %d bits.\n", t);
    // system("pause");
    return 0;
}



