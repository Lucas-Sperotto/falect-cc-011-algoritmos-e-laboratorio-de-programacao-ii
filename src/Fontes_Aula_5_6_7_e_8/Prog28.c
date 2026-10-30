/*
 * ID: A05-08-P28
 * Aula: ../../aulas/aula-07/README.md
 * Objetivo: Mostra a ordenação de estruturas por diferentes campos utilizando qsort().
 */
/* Prog28.c */
/* Algoritmo qsort e binarySearch com estruturas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Exemplo com estrutura */
struct est_pop
{
    char estado[16];
    int pop; /* população */
};

/* qsort - função para comparar struct por população (membro int) */
int struct_cmp_por_pop(const void *a, const void *b)
{
    const struct est_pop *pa = a;
    const struct est_pop *pb = b;
    return (pa->pop > pb->pop) - (pa->pop < pb->pop);	/* Retorna neg. se a<b e pos. se a>b */
}

/* qsort - função para comparar struct por estado (membro C-string) */
int struct_cmp_por_estado(const void *a, const void *b)
{
    const struct est_pop *pa = a;
    const struct est_pop *pb = b;
    return strcmp(pa->estado, pb->estado);
}

int main(void)
{
    unsigned int tamanho, i;
    struct est_pop structs[] = /* população dividido por 1000 */
    { {"Sergipe   ", 1968}, {"Bahia     ", 13815},
        {"Piauí     ", 3007}, {"Acre      ", 670},
        {"Rondônia  ",1535 }, {"Tocantins ", 1306 }
    };

    tamanho = sizeof(structs) / sizeof(struct est_pop);
    /* imprime matriz de estruturas original */
    puts("Estrutura Original");
    for(i=0; i<tamanho; i++)
        printf("[ estado: %s \t população: %6d000 ]\n",
               structs[i].estado, structs[i].pop);
    puts("===============================================");
    /* ordena usando a função qsort */
    qsort(structs, tamanho, sizeof(struct est_pop),
          struct_cmp_por_pop);
    /* imprime matriz de estruturas ordenada */
    puts("Estrutura ordenada por população");
    for(i=0; i<tamanho; i++)
        printf("[ estado: %s \t população: %6d000 ]\n",
               structs[i].estado, structs[i].pop);
    puts("===============================================");
    puts("Estrutura ordenada por estado");
    /* reordena usando a função qsort */
    qsort(structs, tamanho, sizeof(struct est_pop),
          struct_cmp_por_estado);
    /* imprime matriz de estruturas ordenada */
    for(i=0; i<tamanho; i++)
        printf("[ estado: %s \t população: %6d000 ]\n",
               structs[i].estado, structs[i].pop);
    puts("===============================================");
    // system("pause");
    return 0;
}
