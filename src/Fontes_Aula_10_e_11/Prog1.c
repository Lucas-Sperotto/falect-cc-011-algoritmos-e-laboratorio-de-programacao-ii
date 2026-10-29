/*
 * ID: A10-11-P01
 * Aula: ../../atividades/aula-10.md
 * Objetivo: Grava um caractere por vez em um arquivo texto.
 */
/* Prog1.c — grava um caractere por vez em arquivo texto. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fptr = fopen("ArqText.txt", "w");
    int ch, status = 0;
    if (fptr == NULL) { perror("ArqText.txt"); return 1; }
    /* Enter termina a linha no terminal Linux; EOF também encerra a entrada. */
    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (fputc(ch, fptr) == EOF) { status = 1; break; }
    }
    if (ferror(stdin)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    return status;
}
