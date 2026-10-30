/*
 * ID: A10-11-P04
 * Aula: ../../aulas/aula-10/README.md
 * Objetivo: Grava strings em um arquivo texto.
 */
/* Prog4.c — grava strings e exibe o arquivo com a biblioteca C. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fptr = fopen("TesteSTR.txt", "w");
    int status = 0, ch;
    if (fptr == NULL) { perror("TesteSTR.txt"); return 1; }
    if (fputs("Um grande antídoto contra o egoísmo\n"
              "é a generosidade... Dê, mesmo que\n"
              "isso requeira de você um esforço\n"
              "consciente. Pelo fato de partilhar\n"
              "tudo o que possui, seu egoísmo se\n"
              "abrandará.\n", fptr) == EOF) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    if (status) return status;
    /* Substitui o comando Windows system("TYPE TesteSTR.txt"). */
    fptr = fopen("TesteSTR.txt", "r");
    if (fptr == NULL) { perror("TesteSTR.txt"); return 1; }
    while ((ch = fgetc(fptr)) != EOF) {
        if (putchar(ch) == EOF) { status = 1; break; }
    }
    if (ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    // system("PAUSE");
    return status;
}
