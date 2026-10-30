/*
 * ID: A01-P19
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Mostra o uso de strcat().
 */
/* Prog19.c */
/* Mostra o uso de strcat() */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"
#include <string.h>

int main(void)
{
    char salute[100]="Saudações, ";
    char nome[80];

    printf("Digite o seu nome: ");
    /* Histórico: gets(nome); não limita a entrada e saiu do padrão C11. */
    if (!ler_linha(nome, sizeof nome)) {
        fputs("Entrada ausente ou longa demais.\n", stderr);
        return 1;
    }

    /* Há espaço: saudação de 13 bytes + nome de até 79 + terminador < 100. */
    strcat(salute, nome);

    printf("%s\n", salute);

    // system("PAUSE");
    return 0;
}
