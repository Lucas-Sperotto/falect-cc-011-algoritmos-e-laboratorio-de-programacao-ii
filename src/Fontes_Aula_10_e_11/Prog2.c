/*
 * ID: A10-11-P02
 * Aula: ../../aulas/aula-10/README.md
 * Objetivo: Lê um caractere por vez de um arquivo texto.
 */
/* Prog2.c — lê um caractere por vez, verificando a abertura. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fptr = fopen("ArqText.txt", "r");
    /* fgetc() retorna int para representar tanto um byte quanto EOF. */
    int ch, status = 0;
    if (fptr == NULL) { perror("ArqText.txt"); return 1; }
    while ((ch = fgetc(fptr)) != EOF) {
        if (putchar(ch) == EOF) { status = 1; break; }
    }
    if (ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    return status;
}
