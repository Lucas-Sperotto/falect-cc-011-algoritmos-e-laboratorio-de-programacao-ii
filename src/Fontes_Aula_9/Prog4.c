/*
 * ID: A09-P04
 * Aula: ../../aulas/aula-09.md
 * Objetivo: Calculadora bit-a-bit
 */
/* Prog4.c — calculadora de 16 bits; complemento usa "FFFF ~ 0". */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "../entrada_segura.h"

void pbin(unsigned short num);
void pline(void);

int main(void)
{
    char op[3], linha[128], sx1[40], sx2[40], extra[2], *fim;
    unsigned short x1, x2;
    for (;;) {
        printf("\n\nDigite uma expressão (ex. 'FF00 & A23C'; EOF para sair): ");
        /* Tokens limitados; strtoul detecta valores fora da faixa, inclusive
         * aqueles que uma conversão numérica scanf não consegue representar. */
        if (!ler_linha(linha, sizeof linha)) return feof(stdin) ? 0 : 1;
        if (sscanf(linha, "%39s %2s %39s %1s", sx1, op, sx2, extra) != 3) return 1;
        errno = 0;
        unsigned long valor = strtoul(sx1, &fim, 16);
        if (fim == sx1 || *fim != '\0' || sx1[0] == '-' || errno || valor > 0xFFFFUL || valor > USHRT_MAX)
            return 1;
        x1 = (unsigned short)valor;
        errno = 0;
        valor = strtoul(sx2, &fim, 16);
        if (fim == sx2 || *fim != '\0' || sx2[0] == '-' || errno || valor > 0xFFFFUL || valor > USHRT_MAX)
            return 1;
        x2 = (unsigned short)valor;
        pbin(x1);
        switch (op[0]) {
        case '&':
            printf(" & (and)\n"); pbin(x2); pline(); pbin(x1 & x2); break;
        case '|':
            printf(" | (or)\n"); pbin(x2); pline(); pbin(x1 | x2); break;
        case '^':
            printf(" ^ (xor)\n"); pbin(x2); pline(); pbin(x1 ^ x2); break;
        case '>':
        case '<':
            /* A saída tem 16 bits; contagens maiores não pertencem ao exemplo. */
            if (x2 >= 16 || op[1] != op[0]) {
                puts("Deslocamento inválido (use de 0 a 15).");
                return 1;
            }
            printf(" %s %u\n", op, (unsigned int)x2); pline();
            pbin((unsigned short)(op[0] == '>'
                ? (unsigned int)x1 >> x2 : (unsigned int)x1 << x2));
            break;
        case '~':
            printf(" ~ (complemento)\n"); pline(); pbin((unsigned short)~x1); break;
        default:
            puts("Operador inválido."); return 1;
        }
    }
    // system("pause");
    return ferror(stdin) ? 1 : 0;
}

void pbin(unsigned short num)
{
    unsigned short mask = 0x8000;
    printf("%04X\t\t", (unsigned int)num);
    for (int j = 0; j < 16; j++) {
        printf("%d", (mask & num) ? 1 : 0);
        if (j == 7) printf("--");
        mask >>= 1;
    }
    printf("\n");
}

void pline(void)
{
    puts("----------------------------------------");
}
