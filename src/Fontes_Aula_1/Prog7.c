/*
 * ID: A01-P07
 * Aula: ../../atividades/aula-01-pt2.md
 * Objetivo: Imprime 50 combinações de jogos para a Mega-Sena.
 */
/* Loteria.C */
/* Imprime 50 combinações de jogos para a Sena */
#include <stdio.h>
#include <stdlib.h>
#define JOGOS 50
#define N 6
/* As dezenas são independentes e podem repetir: exercício de matrizes
 * e rand(), sem validação das regras de uma aposta real. */

int main(void)
{
    int matriz[JOGOS][N], k, j;

    for(k = 0; k < JOGOS; k++)
        for(j=0 ; j < N; j++)
            matriz[k][j]=rand()%60+1;/*gera núm. aleatório de 1 a 60*/

    for(k = 0; k < JOGOS; k++)
    {
        printf("Combinacao %2d:    ", k+1);
        for(j = 0; j < N; j++)/* Imprime as dezenas na tela*/
            printf("%2d   ",matriz[k][j]);
        printf("\n");
    }
    // system("PAUSE");
    return 0;
}
