/* Prog25.c */
/* Algoritmo qsort com inteiros */
#include <stdio.h>
#include <stdlib.h>

int compara(const void *, const void *);

int main()
{
    unsigned int tamanho, i;

    int tab[]= { 234, 760, 162, 890, -23, 914, 567, 888, 398, -45};

    tamanho = sizeof(tab)/sizeof(int);

    qsort(tab, tamanho, sizeof(int), compara);

    for(i=0; i< 8; i++) printf("%d\n", tab[i]);
    // system("pause");
    return 0;
}

/* qsort - função para comparar inteiros */
int compara(const void *a, const void *b)
{
    const int *pa = (const int *)a; /* modifica o tipo do ponteiro */
    const int *pb = (const int *)b; /* modifica o tipo do ponteiro */
    return *pa  - *pb; 	/* Retorna negativo se a<b e positivo se a > b  */
}
