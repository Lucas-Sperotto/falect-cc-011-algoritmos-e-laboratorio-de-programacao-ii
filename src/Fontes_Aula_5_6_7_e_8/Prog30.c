/*
 * ID: A05-08-P30
 * Aula: ../../aulas/aula-08/README.md
 * Objetivo: Mostra alocação dinâmica de vetores utilizando calloc().
 */
/* Prog30.c */
/* Alocação dinâmica da matriz com calloc() */
#include <stdio.h>
#include <stdlib.h>

float media(float *, int );/*protótipo */

int main(void)
{
    float *notas , m;
    int tamanho, i;

    puts("Qual é o número de notas? ");
    if (scanf("%d", &tamanho) != 1 || tamanho <= 0 || tamanho > 100000)
        return 1; /* Limite didático para não alocar volumes excessivos. */

    notas = calloc((size_t)tamanho, sizeof *notas);
    if (notas == NULL) return 1;

    for(i=0; i < tamanho; i++)
    {
        printf("Digite a nota do aluno %d: ", i + 1);
        if (scanf("%f", notas+i) != 1) { free(notas); return 1; }
    }

    m = media( notas, tamanho );
    printf("Média das notas: %.2f\n", m);

    free(notas);
    notas = NULL;

    // system("PAUSE");
    return 0;
}

/* Calcula a média dos valores da matriz */
float media(float *lista, int tamanho)
{
    int i;
    double m=0.0; /* Soma de float finitos pode exceder FLT_MAX. */
    for(i=0; i < tamanho ; i++) m += *(lista++);
    return  m/tamanho;
}
