/*
 * ID: A01-P21
 * Aula: ../../atividades/aula-02.md
 * Objetivo: Mostra o uso de strcmp().
 */
/* Prog21.c */
/* Mostra o uso de strcmp() */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"
#include <string.h>

int main(void)
{
    char resposta[]="BRANCO";
    char resp[40];

    printf("Qual é a cor do cavalo branco de Napoleão?");
    /* Histórico: gets(resp); não limita a entrada e saiu do padrão C11. */
    if (!ler_linha(resp, sizeof resp)) {
        fputs("Entrada ausente ou longa demais.\n", stderr);
        return 1;
    }

    while (strcmp(resp,resposta) != 0)
    {
        printf("Resposta errada. Tente de novo.\n");
        /* Histórico: gets(resp); não limita a entrada e saiu do padrão C11. */
        if (!ler_linha(resp, sizeof resp)) {
            fputs("Entrada ausente ou longa demais.\n", stderr);
            return 1;
        }
    }
    printf("Correto!\n");
    // system("PAUSE");
    return 0;
}
