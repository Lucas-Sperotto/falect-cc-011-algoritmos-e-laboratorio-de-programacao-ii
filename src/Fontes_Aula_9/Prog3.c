/*
 * ID: A09-P03
 * Aula: ../../aulas/aula-09.md
 * Objetivo: um no bit mais significativo e zero nos outros
 */
/* Prog3.c — converte hexadecimal em binário. */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include "../entrada_segura.h"

int palavra(void);

int main(void)
{
    unsigned int num, mask;
    int t = palavra();
    for (;;) {
        printf("\nDigite um número em hexadecimal (EOF para sair): ");
        char linha[80], *fim, *inicio;
        unsigned long valor;
        if (!ler_linha(linha, sizeof linha)) return feof(stdin) ? 0 : 1;
        inicio = linha;
        while (isspace((unsigned char)*inicio)) inicio++;
        errno = 0;
        valor = strtoul(inicio, &fim, 16);
        if (fim == inicio || *inicio == '-' || errno || valor > UINT_MAX) return 1;
        while (isspace((unsigned char)*fim)) fim++;
        if (*fim != '\0') return 1;
        num = (unsigned int)valor;
        /* Deslocamento unsigned evita o cálculo de máscara em ponto flutuante. */
        mask = 1U << (t - 1);
        printf("Binário de %04x é: ", num);
        for (int j = 0; j < t; j++) {
            printf("%d", (mask & num) ? 1 : 0);
            if ((j + 1) % 8 == 0) printf("--");
            mask >>= 1;
        }
    }
    // system("pause");
    return ferror(stdin) ? 1 : 0;
}

int palavra(void)
{
    unsigned int n = ~0U;
    int i;
    for (i = 0; n; i++) n <<= 1;
    return i;
}
