/*
 * ID: A01-P12
 * Aula: ../../aulas/aula-01/README.md
 * Objetivo: Mostra matriz de duas dimensões como argumento de função.
 */
/* Histograma.C */
/* Mostra matriz de duas dimensões como argumento de função */
#include <stdio.h>
#include <stdlib.h>
#define MES 3
#define FUNC 5

void histograma( int [][MES], int);/* protótipo */

int main(void)
{
    int pecas[FUNC][MES], i, j;

    for(i=0; i<FUNC ; i++)
        for(j=0; j<MES ; j++)
        {
            printf("Funcionário: %d\tmês %d: ", i+1, j+1);
            if (scanf("%d", &pecas[i][j]) != 1 || pecas[i][j] < 0) {
                fputs("Quantidade inválida.\n", stderr);
                return 1;
            }
        }
    histograma(pecas,FUNC);
    // system("PAUSE");
    return 0;
}
/* Imprime um histograma horizontal */
void histograma( int pecas[][MES], int nfunc)
{
    const double MAXBARRA=50.0;
    long long max=0, temp;
    int i, j, tam;

    for(i=0; i<nfunc; i++)
    {
        temp=0; /* Total de cada funcionário, sem acumular os anteriores. */
        for(j=0; j<MES ; j++)
            temp += pecas[i][j];
        if(max < temp)	max=temp;
    }

    for( i=0 ; i<nfunc; i++)
    {
        temp=0;
        for( j=0; j<MES ; j++) temp += pecas[i][j];
        printf("%2d - %5lld:", i+1, temp);

        /* Sem produção, todas as barras têm tamanho zero. */
        tam = max == 0 ? 0 : (int)((double)temp/(double)max*MAXBARRA);

        for(j=0; j<tam; j++) printf("*");
        printf("\n");
    }
}
