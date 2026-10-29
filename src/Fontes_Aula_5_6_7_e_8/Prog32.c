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

    system("PAUSE");
    return 0;
}
