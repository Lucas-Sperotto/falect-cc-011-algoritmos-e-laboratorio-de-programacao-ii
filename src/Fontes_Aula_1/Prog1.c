/*
 * ID: A01-P01
 * Aula: ../../atividades/aula-01-pt1.md
 * Objetivo: Calcula a média de cinco notas (não usa matriz).
 */
/* Notas.C */
/* Calcula a média de 5 notas (não usa matriz) */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int nota0, nota1, nota2, nota3, nota4;
    float media = 0.0;

    printf("Digite a nota do aluno 1 ");
    if (scanf("%d", &nota0) != 1) {
        fputs("Nota inválida.\n", stderr);
        return 1;
    }
    printf("Digite a nota do aluno 2 ");
    if (scanf("%d", &nota1) != 1) {
        fputs("Nota inválida.\n", stderr);
        return 1;
    }
    printf("Digite a nota do aluno 3 ");
    if (scanf("%d", &nota2) != 1) {
        fputs("Nota inválida.\n", stderr);
        return 1;
    }
    printf("Digite a nota do aluno 4 ");
    if (scanf("%d", &nota3) != 1) {
        fputs("Nota inválida.\n", stderr);
        return 1;
    }
    printf("Digite a nota do aluno 5 ");
    if (scanf("%d", &nota4) != 1) {
        fputs("Nota inválida.\n", stderr);
        return 1;
    }

    /* A conversão antes da soma evita overflow na soma de inteiros. */
    media = ((double)nota0 + nota1 + nota2 + nota3 + nota4) / 5.0;
    printf("Média das notas: %.2f\n", media);

    // system("PAUSE");
    return 0;
}
