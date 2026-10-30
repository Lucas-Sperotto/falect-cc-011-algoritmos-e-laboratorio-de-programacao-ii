/*
 * ID: A10-11-P09
 * Aula: ../../aulas/aula-10/README.md
 * Objetivo: Conta os bytes de um arquivo aberto em modo binário.
 */
/* Prog9.c — conta bytes em modo binário. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    FILE *fptr;
    int ch, status = 0;
    size_t cont = 0;
    if (argc != 2) { fprintf(stderr, "Uso: %s nomearq\n", argv[0]); return 1; }
    fptr = fopen(argv[1], "rb");
    if (fptr == NULL) { perror(argv[1]); return 1; }
    /* Linux não traduz CRLF em modo texto; cada fgetc conta um byte. */
    while ((ch = fgetc(fptr)) != EOF) {
        if (cont == SIZE_MAX) { status = 1; break; }
        cont++;
    }
    if (ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    if (!status) printf("O tamanho do arquivo é %zu bytes.\n", cont);
    return status;
}
