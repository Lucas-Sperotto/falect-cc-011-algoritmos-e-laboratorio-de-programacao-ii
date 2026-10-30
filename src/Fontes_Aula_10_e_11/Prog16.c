/*
 * ID: A10-11-P16
 * Aula: ../../aulas/aula-11/README.md
 * Objetivo: Envia o conteúdo de um arquivo para uma impressora.
 */
/* Prog16.c — envia linhas a um destino de saída. */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char buff[80];
    int status = 0;
    FILE *fptr = fopen("FilePrint.C", "r");
    /* Histórico: fopen("PRN", "w") acessava a impressora no Windows.
     * No Linux, PRN seria apenas um arquivo comum; usamos a saída padrão.
     * Para imprimir, o estudante pode redirecionar a saída conscientemente. */
    FILE *fprn = stdout;
    if (fptr == NULL) { perror("FilePrint.C"); return 1; }
    while (fgets(buff, sizeof buff, fptr) != NULL) {
        if (fputs(buff, fprn) == EOF) { status = 1; break; }
    }
    if (ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    if (fflush(fprn) == EOF) status = 1;
    // system("pause");
    return status;
}
