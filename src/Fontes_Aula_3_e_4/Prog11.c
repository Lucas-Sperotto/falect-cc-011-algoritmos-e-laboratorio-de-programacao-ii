/*
 * ID: A03-04-P11
 * Aula: ../../atividades/aulas-03-e-04.md
 * Objetivo: Mostra o uso do operador sizeof().
 */
/* Prog11.c */
/* Mostra o uso do operador sizeof() */
#include <stdio.h>
#include <stdlib.h>

union Numero
{
    char str[32];
    int i;
    float f;
} x; /* Cria variável */

int main(void)
{
    printf("%zu\n", sizeof(union Numero));
    printf("%zu\n", sizeof(x));

    // system("PAUSE");
    return 0;
}
