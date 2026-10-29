/*
 * ID: A01-P05
 * Aula: ../../atividades/aula-01-pt1.md
 * Objetivo: Calcula a média das notas de qualquer número de alunos.
 */
/* NotasF1.C */
/* Calcula a média das notas de qualquer número de alunos */
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 50

int main(void)
{

    float notas[TAMANHO];
    double media=0.0; /* Acumulação evita overflow com notas float finitas. */
    int i=0,j;

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
    if (i == TAMANHO) printf("BUFFER LOTADO.\n");
    if (i == 0) {
        fputs("Nenhuma nota informada.\n", stderr);
        return 1;
    }

    for(j=0 ; j < i ; j++)
        media += notas[j];

    media /= i;
    printf("Média das notas: %.2f\n", media);

    // system("PAUSE");
    return 0;
}

