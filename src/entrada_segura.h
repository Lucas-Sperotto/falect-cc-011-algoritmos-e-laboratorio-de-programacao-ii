#ifndef ENTRADA_SEGURA_H
#define ENTRADA_SEGURA_H

#include <limits.h>
#include <stdio.h>
#include <string.h>

/* Alternativa limitada a gets(): remove a quebra e rejeita linhas excessivas.
 * Retorna 1 na leitura completa e 0 em EOF, erro ou truncamento.
 * O restante de uma linha longa é consumido para não virar a próxima entrada.
 */
static inline int ler_linha(char *destino, size_t capacidade)
{
    int ch;
    char *quebra;
    if (capacidade < 2 || capacidade > INT_MAX ||
        fgets(destino, (int)capacidade, stdin) == NULL)
        return 0;
    quebra = strchr(destino, '\n');
    if (quebra != NULL) {
        *quebra = '\0';
        if (quebra > destino && quebra[-1] == '\r')
            quebra[-1] = '\0';
        return 1;
    }
    ch = getchar();
    if (ch == '\n' || (ch == EOF && !ferror(stdin)))
        return 1;
    while (ch != '\n' && ch != EOF)
        ch = getchar();
    destino[0] = '\0';
    return 0;
}

#endif
