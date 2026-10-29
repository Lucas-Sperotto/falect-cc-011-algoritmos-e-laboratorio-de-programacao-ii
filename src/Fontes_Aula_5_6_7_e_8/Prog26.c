/* Prog26.c */
/* Algoritmo qsort e binarySearch com inteiros */
#include <stdio.h>
#include <stdlib.h>

/* Função procura binária para inteiros
 * procura entre MatrizOrdenada[inicio]..MatrizOrdenada[fim] pela chave.
 * retorna o índice do elemento encontrado ou -1 se não foi encontrado */
int binarySearchInt(int MatrizOrdenada[], int inicio, int fim, int chave)
{
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;  /* divide ao meio */
        if (chave > MatrizOrdenada[meio])
            inicio = meio + 1;  /* repete a procura a partir do meio */
        else if (chave < MatrizOrdenada[meio])
            fim = meio - 1; /* repete a procura até o meio */
        else
            return meio;     /* encontrado, retorna posição */
    }
    return -1; /* não foi encontrado */
}

/* qsort - função para comparar inteiros */
int compara(const void *a, const void *b)
{
    const int *pa = (const int *)a; /* modifica o tipo do ponteiro */
    const int *pb = (const int *)b; /* modifica o tipo do ponteiro */
    return *pa  - *pb; 	/* Retorna negativo se a<b e positivo se a > b  */
}

int main()
{
    unsigned int tamanho, i, procura;

    int tab[]= { 234, 760, 162, 890, -23, 914, 567, 888, 398, -45};
    printf("\nMatriz Original\n");
    for(i=0; i< 8; i++) printf("%d\n", tab[i]);
    tamanho = sizeof(tab)/sizeof(int);

    qsort(tab, tamanho, sizeof(int), compara);
    printf("\nMatriz Ordenada\n");
    for(i=0; i< 8; i++) printf("%d\n", tab[i]);

    procura = binarySearchInt(tab, 0, tamanho - 1, 567);
    printf("\n\nIndice de 567 = %d\n",procura);

    // system("pause");
    return 0;
}

