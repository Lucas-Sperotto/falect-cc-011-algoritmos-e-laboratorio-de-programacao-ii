/*
 * ID: A01-P14
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Mostra leitura de string com gets().
 */
/* Prog14.c */
/* Mostra a alternativa limitada à antiga leitura com gets(). */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"

int main(void)
{
    char nome[80];
    printf("Digite o seu nome: ");
    /* Histórico: gets(nome); não limita a entrada e saiu do padrão C11. */
    if (!ler_linha(nome, sizeof nome)) {
        fputs("Entrada ausente ou longa demais.\n", stderr);
        return 1;
    }
    printf("Saudações %s.\n", nome);
    // system("PAUSE");
    return 0;
}

