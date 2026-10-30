/*
 * ID: A09-P01
 * Aula: ../../aulas/aula-09/README.md
 * Objetivo: Mostra o uso do operador de complemento ~
 */
/* Prog1.c — complemento dos bytes digitados, até X ou EOF. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int ch;
    /* getchar() permite distinguir todos os bytes de EOF; conio.h era Windows. */
    while ((ch = getchar()) != EOF && ch != 'X')
        if (putchar((unsigned char)~(unsigned char)ch) == EOF)
            return 1;
    // system("pause");
    return ferror(stdin) || ferror(stdout) ? 1 : 0;
}
