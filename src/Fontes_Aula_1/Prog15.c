/*
 * ID: A01-P15
 * Aula: ../../atividades/aula-02.md
 * Objetivo: Mostra impressão de string com puts().
 */
/* Prog15.c */
/* Mostra impressão de string com puts() */
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
    puts("Saudacoes, ");/* imprime texto no vídeo */
    puts(nome);
    puts("puts() pula de linha sozinha");
    /* Só forma a substring se o deslocamento pertence à string. */
    if (strlen(nome) >= 4)
        puts(&nome[4]);
    // system("PAUSE");
    return 0;
}
