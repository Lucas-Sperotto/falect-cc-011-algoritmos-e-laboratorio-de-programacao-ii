/*
 * ID: A10-11-P11
 * Aula: ../../aulas/aula-11/README.md
 * Objetivo: Grava estruturas de dados em um arquivo binário.
 */
/* Prog11.c — grava estruturas em disco. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <math.h>
#include "../entrada_segura.h"

/* Formato didático nativo: padding, endian e tamanhos dependem da ABI.
 * Leia somente arquivos gerados por estes exemplos na mesma plataforma. */
typedef struct Livro {
    char Titulo[50];
    char Autor[50];
    short NumReg;
    double Preco;
} Livro;

/* gets() foi removida em C11; cada campo recebe uma linha limitada. */
int GetLivro(Livro *livro)
{
    char linha[80], *fim;
    long registro;
    memset(livro, 0, sizeof *livro);
    printf("\n\tDigite o título: ");
    if (!ler_linha(livro->Titulo, sizeof livro->Titulo)) return 0;
    printf("\tDigite o nome do autor: ");
    if (!ler_linha(livro->Autor, sizeof livro->Autor)) return 0;
    printf("\tDigite o número do registro: ");
    if (!ler_linha(linha, sizeof linha)) return 0;
    errno = 0;
    registro = strtol(linha, &fim, 10);
    if (fim == linha || *fim != '\0' || errno || registro < SHRT_MIN || registro > SHRT_MAX)
        return 0;
    livro->NumReg = (short)registro;
    printf("\tDigite o preço: ");
    if (!ler_linha(linha, sizeof linha)) return 0;
    errno = 0;
    livro->Preco = strtod(linha, &fim);
    return fim != linha && *fim == '\0' && errno == 0 && isfinite(livro->Preco);
}

int main(void)
{
    Livro livro;
    char resp[3];
    int status = 0;
    FILE *fptr = fopen("Livros.Dat", "wb");
    if (fptr == NULL) { perror("Livros.Dat"); return 1; }
    do {
        if (!GetLivro(&livro)) {
            fputs("Entrada incompleta ou inválida.\n", stderr); status = 1; break;
        }
        if (fwrite(&livro, sizeof livro, 1, fptr) != 1) { status = 1; break; }
        printf("Mais um livro (s/n)? ");
        /* EOF após um registro completo também encerra a gravação. */
        if (!ler_linha(resp, sizeof resp)) break;
    } while (resp[0] != 'n' && resp[0] != 'N');

    if (ferror(stdin)) status = 1;

    if (fclose(fptr) == EOF) status = 1;
    // system("pause");
    return status;
}
