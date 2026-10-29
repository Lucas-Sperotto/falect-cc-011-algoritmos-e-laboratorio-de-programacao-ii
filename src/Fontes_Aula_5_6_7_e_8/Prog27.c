/* Prog27.c */
/* Algoritmo qsort e binarySearch com C-string */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Função procura binária para C-string
 * procura entre MatrizOrdenada[inicio]..MatrizOrdenada[fim] pela chave.
 * retorna o índice do elemento encontrado ou -1 se não foi encontrado */
int binarySearchStr(char *MatrizOrdenada[],int inicio,int fim,char*chave)
{
    while (inicio <= fim)
    {
        int meio = (inicio + fim) / 2;  /* divide ao meio */
        int cmp = strcmp(chave, MatrizOrdenada[meio]);

        if (cmp > 0)
            inicio = meio + 1; /* repete a procura a partir do meio */
        else if (cmp < 0)
            fim = meio - 1; 	 /* repete a procura até o meio */
        else
            return meio;     	 /* encontrado, retorna posição */
    }
    return -1;    		 /* não foi encontrado */
}

/* qsort - função para comparar C-string (matriz char) */
int cstring_cmp(const void *a, const void *b)
{
    const char **pa = (const char **)a;
    const char **pb = (const char **)b;
    return strcmp(*pa, *pb);
    /* strcmp -1 se a < b, 1 se a>b e 0 se a==b*/
}

int main()
{
    unsigned int tamanho, i, procura;
    char *strings[] = { "Zuleima", "Andre", "Carolina",
                        "Beto", "Fabio", "Denise"
                      };
    tamanho = sizeof(strings) / sizeof(char *);
    puts("Matriz Original");
    for(i=0; i< tamanho; i++) printf("%s\n", strings[i]);

    qsort(strings, tamanho, sizeof(char *), cstring_cmp);

    puts("\nMatriz Ordenada");
    for(i=0; i< tamanho; i++) printf("%s\n", strings[i]);

    procura = binarySearchStr(strings, 0, 5, "Carolina");
    printf("\nIndice de Carolina = %d\n",procura);

    system("pause");
    return 0;
}
