/*
 * ID: A01-P22
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Testa a função strcmp().
 */
/* Prog22.c */
/* Testa a função strcmp() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    /* Apenas o sinal do resultado é definido; a magnitude pode variar. */
    printf("%d\n", strcmp("A", "A"));
    printf("%d\n", strcmp("A", "B"));
    printf("%d\n", strcmp("B", "A"));
    printf("%d\n", strcmp("C", "A"));
    printf("%d\n", strcmp("casas", "casa"));

    // system("PAUSE");
    return 0;
}
