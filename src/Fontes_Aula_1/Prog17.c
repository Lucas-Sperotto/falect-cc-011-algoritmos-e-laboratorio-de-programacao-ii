/*
 * ID: A01-P17
 * Aula: ../../atividades/aula-02.md
 * Objetivo: Mostra o uso da aritmética com endereços.
 */
/* Prog17.c */
/* Mostra o uso da aritmética com endereços */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"

int main(void)
{
    char salute[]="Saudações, ";
    char nome[80];
    printf("Digite o seu nome: ");
    /* Histórico: gets(nome); não limita a entrada e saiu do padrão C11. */
    if (!ler_linha(nome, sizeof nome)) {
        fputs("Entrada ausente ou longa demais.\n", stderr);
        return 1;
    }
    if (strlen(nome) < 5) {
        fputs("Informe um nome com pelo menos cinco bytes.\n", stderr);
        return 1;
    }
    printf("%s%s\n", salute, nome + 5);
    // system("PAUSE");
    return 0;
}
