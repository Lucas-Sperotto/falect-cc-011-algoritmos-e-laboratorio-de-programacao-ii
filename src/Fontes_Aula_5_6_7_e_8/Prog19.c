/*
 * ID: A05-08-P19
 * Aula: ../../aulas/aula-07/README.md
 * Objetivo: Mostra a passagem de ponteiros para funções como argumentos.
 */
/* Prog19.c */
/* Mostra o uso de ponteiro como argumento de função */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"

void func( int (*)(char *, size_t));

int main(void)
{
    int (*p)(char *, size_t);
    p = ler_linha; /* Leitura limitada substitui a antiga gets(). */
    func(p);

    // system("PAUSE");
    return 0;
}

void func(int (*p)(char *, size_t))
{
    char nome[80];

    printf("Digite seu nome: ");

    if (!(*p)(nome, sizeof nome)) return; /* Chama por ponteiro. */

    printf("Seu nome é: %s\n", nome);
}
