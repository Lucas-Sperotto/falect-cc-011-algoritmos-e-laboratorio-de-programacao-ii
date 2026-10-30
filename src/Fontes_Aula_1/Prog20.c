/*
 * ID: A01-P20
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Mostra o uso de cinco operações entre strings.
 */
/* Prog20.c */
/* Mostra a comparação entre strings */
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

    /* Histórico: while (resp != resposta) comparava endereços e nunca
     * terminava, mesmo com BRANCO. Avaliamos uma vez para estudar o erro;
     * a comparação do conteúdo com strcmp() aparece no Prog21.c. */
    if (&resp[0] != &resposta[0])
        printf("Endereços diferentes, mesmo que o conteúdo seja BRANCO.\n");
    printf("Para comparar o conteúdo, consulte Prog21.c.\n");
    // system("PAUSE");
    return 0;
}

