/*
 * ID: A10-11-P06
 * Aula: ../../aulas/aula-10/README.md
 * Objetivo: Grava dados formatados em um arquivo utilizando fprintf().
 */
/* Prog6.c — grava dados formatados; título sem espaços, até 29 bytes. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <string.h>


/* scanf/fscanf limitam os tokens; as conversões numéricas verificam a faixa. */
static int converte(const char *registro, const char *valor, int *regnum, double *preco)
{
    char *fim;
    errno = 0;
    long numero = strtol(registro, &fim, 10);
    if (fim == registro || *fim != '\0' || errno || numero < INT_MIN || numero > INT_MAX)
        return 0;
    *regnum = (int)numero;
    errno = 0;
    *preco = strtod(valor, &fim);
    return fim != valor && *fim == '\0' && errno == 0 && isfinite(*preco);
}

int main(void)
{
    FILE *fptr = fopen("Livros.txt", "w");
    char titulo[30], registro[80], valor[80];
    int regnum, status = 0;
    double preco;
    if (fptr == NULL) { perror("Livros.txt"); return 1; }
    for (;;) {
        printf("\nDigite titulo, registro e preco do livro (EOF encerra): ");
        int lidos = scanf("%29s %79s %79s", titulo, registro, valor);
        if (lidos == EOF) break;
        if (lidos != 3) { status = 1; break; }
        if (strlen(titulo) <= 1) break;
        if (!converte(registro, valor, &regnum, &preco)) { status = 1; break; }
        if (fprintf(fptr, "%s %d %.2f\n", titulo, regnum, preco) < 0) {
            status = 1; break;
        }
    }
    if (ferror(stdin)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    // system("pause");
    return status;
}
