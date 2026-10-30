/*
 * ID: A05-08-P31
 * Aula: ../../aulas/aula-08/README.md
 * Objetivo: Mostra a implementação de uma lista encadeada de livros.
 */
/* Prog31.c */
/* Mostra a implementação de uma lista ligada */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "../entrada_segura.h"

typedef struct Livro
{
    char Titulo[30];
    char Autor[30];
    int  NumReg;
    double Preco;
    struct Livro *Proximo;
} Livro;

Livro *primeiro, *atual, *NovoLivro;

int GetLivro(void)
{
    char temp[80], *fim;
    long registro;
    NovoLivro = malloc(sizeof *NovoLivro);
    if (NovoLivro == NULL) return 0;
    /* Só encadeia o livro depois de completar todas as leituras. */
    printf("Digite titulo: ");
    if (!ler_linha(NovoLivro->Titulo, sizeof NovoLivro->Titulo)) goto falha;
    printf("Digite autor: ");
    if (!ler_linha(NovoLivro->Autor, sizeof NovoLivro->Autor)) goto falha;
    printf("Digite o número do registro: ");
    if (!ler_linha(temp, sizeof temp)) goto falha;
    errno = 0;
    registro = strtol(temp, &fim, 10);
    if (errno || fim == temp || *fim || registro < INT_MIN || registro > INT_MAX)
        goto falha;
    NovoLivro->NumReg = (int)registro;
    printf("Digite o preço: ");
    if (!ler_linha(temp, sizeof temp)) goto falha;
    errno = 0;
    NovoLivro->Preco = strtod(temp, &fim);
    if (errno || fim == temp || *fim || !isfinite(NovoLivro->Preco)) goto falha;
    NovoLivro->Proximo = NULL;
    if (primeiro == NULL)
        primeiro = atual = NovoLivro;
    else
    {
        atual = primeiro;
        while (atual->Proximo != NULL)
            atual = atual->Proximo;
        atual->Proximo = NovoLivro;
        atual = NovoLivro;
    }
    return 1;
falha:
    free(NovoLivro);
    NovoLivro = NULL;
    return 0;
}

void PrintLivro(void)
{
    if (primeiro == NULL)
    {
        puts("Lista vazia");
        return;
    }
    atual = primeiro;
    do
    {
        printf("Título: %s\n", atual->Titulo);
        printf("Autor : %s\n", atual->Autor);
        printf("No.Reg: %d\n", atual->NumReg);
        printf("Preço : %.2f\n\n", atual->Preco);
        atual = atual->Proximo;
    }
    while (atual != NULL);
}

void LiberaLivros(void)
{
    while (primeiro != NULL)
    {
        atual = primeiro;
        primeiro = primeiro->Proximo;
        free(atual);
    }
    atual = NovoLivro = NULL;
}

int main(void)
{
    char resposta[8];
    primeiro = NULL;
    do
    {
        if (!GetLivro()) { LiberaLivros(); return 1; }
        puts("\nInserir outro livro (s/n)? ");
        if (!ler_linha(resposta, sizeof resposta)) break;
    }
    while (resposta[0] != 'n' && resposta[0] != 'N');

    puts("\nLISTA DOS LIVROS CADASTRADOS");
    puts("============================");
    PrintLivro();
    LiberaLivros();
    // system("PAUSE");
    return 0;
}
