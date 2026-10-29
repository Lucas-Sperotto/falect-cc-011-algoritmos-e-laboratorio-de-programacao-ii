/*
 * ID: A01-P16
 * Aula: ../../atividades/aula-02.md
 * Objetivo: Mostra o uso de strings inicializadas.
 */
/* Prog16.c */
/* Mostra o uso de strings inicializadas */
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
    printf("%s%s\n", salute, nome);
    // system("PAUSE");
    return 0;
}
