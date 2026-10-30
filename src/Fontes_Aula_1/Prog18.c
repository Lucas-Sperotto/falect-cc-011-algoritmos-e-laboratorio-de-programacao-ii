/*
 * ID: A01-P18
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Mostra o uso de strlen().
 */
/* Prog18.c */
/* Mostra o uso de strlen() */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"
#include <string.h>

int main(void)
{
    size_t len, i;
    char nome[80];

    printf("Digite o seu nome: ");
    /* Histórico: gets(nome); não limita a entrada e saiu do padrão C11. */
    if (!ler_linha(nome, sizeof nome)) {
        fputs("Entrada ausente ou longa demais.\n", stderr);
        return 1;
    }

    len=strlen(nome);

    /* Exibe a string e seu terminador; posições seguintes não são texto. */
    for(i=0; i<=len; i++)
        printf("Endereço = %p\tChar  = %c\tDec   = %d\n",
               (void *)(nome+i), nome[i], (int)(unsigned char)nome[i]);

    // system("PAUSE");
    return 0;
}
