/*
 * ID: A01-P10
 * Aula: ../../aulas/aula-01/README.md
 * Objetivo: Mostra a passagem de matrizes para funções como argumento.
 */
/* Prog10.C */
/* Mostra a passagem de matrizes para funções como argumento */
#include <stdio.h>
#include <stdlib.h>
#define TAMANHO 50

float media(float[], int); /*Protótipo*/

int main(void)
{
    float notas[TAMANHO], m;
    int i=0;

    /* O limite é verificado antes de escrever no vetor. */
    while (i < TAMANHO)
    {
        printf("Digite a nota do aluno %d ", i+1);
        if (scanf("%f", &notas[i]) != 1) {
            fputs("Nota inválida.\n", stderr);
            return 1;
        }
        if (notas[i] < 0.0)
            break; /* A sentinela não entra no cálculo. */
        i++;
    }
    if (i == 0) {
        fputs("Nenhuma nota informada.\n", stderr);
        return 1;
    }

    m = media(notas, i);

    printf("Média das notas: %.2f\n", m);

    // system("PAUSE");
    return 0;
}

float media(float lista[], int tamanho)
{
    int i;
    double m = 0.0; /* Soma de float finitos pode exceder FLT_MAX. */
    for(i=0 ; i < tamanho ; i++)m += lista[i];
    return m/tamanho;
}
