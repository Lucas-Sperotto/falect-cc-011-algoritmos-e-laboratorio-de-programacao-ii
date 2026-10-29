/*
 * ID: A05-08-P14
 * Aula: ../../atividades/aulas-06-e-07.md
 * Objetivo: Mostra o uso de ponteiros para cadeias de caracteres.
 */
/* Prog14.c */
/* Mostra o uso de ponteiro para cadeias de caracteres */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char s1[] = "Saudações!";
    const char *s2 = "Saudações!";

    printf("%p\n", (void *)s1);
    printf("%p\n", (void *)s2);

    /* s1++;  ERRO intencional: o nome do array não é uma variável ponteiro. */
    s2++; /* OK */

    printf("%s\n", s2); /* Imprime: audações! */
    return 0;
}
