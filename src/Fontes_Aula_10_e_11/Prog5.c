/*
 * ID: A10-11-P05
 * Aula: ../../atividades/aula-10.md
 * Objetivo: Lê um arquivo texto linha por linha.
 */
/* Prog5.c — lê linha a linha do arquivo. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fptr = fopen("TesteSTR.txt", "r");
    char str[81];
    int status = 0;
    if (fptr == NULL) { perror("TesteSTR.txt"); return 1; }
    while (fgets(str, sizeof str, fptr) != NULL) {
        if (fputs(str, stdout) == EOF) { status = 1; break; }
    }
    if (ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    // system("pause");
    return status;
}
