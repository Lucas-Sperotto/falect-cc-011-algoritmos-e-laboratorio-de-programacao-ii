/*
 * ID: A05-08-P16
 * Aula: ../../atividades/aulas-06-e-07.md
 * Objetivo: Mostra o uso de ponteiros para ponteiros na ordenação de strings.
 */
/* Prog16.c */
/* Mostra o uso de ponteiros para ponteiros */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../entrada_segura.h"
#define NOME_MAX 30
#define TAM_MAX 100

void ordena(char **p,int n)
{
    char *temp;
    int i,j;

    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
            if( strcmp(p[i],p[j])>0)
            {
                temp = *(p+i);
                *(p+i) = *(p+j);
                *(p+j) = temp;
            }
    }
}

int main(void)
{
    char nomes[NOME_MAX][TAM_MAX];
    char *p[NOME_MAX]; /* matriz de ponteiros */
    int n, i;

    for( n=0; n<NOME_MAX; n++)
    {
        printf("Digite nome ou [ENTER] para fim: ");
        if (!ler_linha(nomes[n], sizeof nomes[n])) return 1;
        if(strlen(nomes[n])==0) break;
        p[n] = nomes[n];
    }

    printf("\n\nLista original:\n");
    for(i=0; i<n; i++)
        printf("%s\n", p[i]);

    ordena(p,n);

    printf("\n\nLista ordenada:\n");
    for(i=0; i<n; i++)
        printf("%s\n", p[i]);

    // system("PAUSE");
    return 0;
}
