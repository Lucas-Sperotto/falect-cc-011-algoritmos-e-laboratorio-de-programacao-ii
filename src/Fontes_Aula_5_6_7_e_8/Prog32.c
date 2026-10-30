/*
 * ID: A05-08-P32
 * Aula: ../../aulas/aula-08/README.md
 * Objetivo: Mostra a utilização de argumentos da linha de comando (argc e argv).
 */
/* Prog32.c */
/* Mostra argumentos da linha de comando */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) /* int main(int argc, char *argv[]) */
{
    int i;

    printf("Número de argumentos: %d\n", argc);

    for(i=0; i<argc; i++)
        printf("Argumento número %d: %s\n", i, argv[i]);

    // system("PAUSE");
    return 0;
}
