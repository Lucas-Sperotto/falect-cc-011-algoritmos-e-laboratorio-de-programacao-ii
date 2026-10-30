/*
 * ID: A10-11-P07
 * Aula: ../../aulas/aula-10/README.md
 * Objetivo: Lê dados formatados de um arquivo utilizando fscanf().
 */
/* Prog7.c — lê dados formatados do arquivo. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>


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
    FILE *fptr = fopen("Livros.txt", "r");
    char titulo[30], registro[80], valor[80];
    int regnum, lidos, status = 0;
    double preco;
    if (fptr == NULL) { perror("Livros.txt"); return 1; }
    /* Só imprime registros completos; uma conversão parcial não é EOF. */
    while ((lidos = fscanf(fptr, "%29s %79s %79s", titulo, registro, valor)) == 3) {
        if (!converte(registro, valor, &regnum, &preco)) { status = 1; break; }
        if (printf("%s %d %.2f\n", titulo, regnum, preco) < 0) {
            status = 1; break;
        }
    }
    if (lidos != EOF || ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    // system("pause");
    return status;
}
