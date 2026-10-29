/*
 * ID: A01-P03
 * Aula: ../../atividades/aula-01-pt1.md
 * Objetivo: Calcula a média das notas de cinco alunos usando matriz float.
 */
/* NotasF.C */
/* Calcula a média das notas de 5 alunos usando matriz float */
#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 5 /* não podemos usar const */

int main(void)
{

    float notas[TAMANHO] , media=0.0;
    int i;

    for( i=0 ; i < TAMANHO ; i++ )
    {
        printf("Digite a nota do aluno %d ", i+1);
        if (scanf("%f", &notas[i]) != 1) {
            fputs("Entrada inválida.\n", stderr);
            return 1;
        }
        media += notas[i];
    }
    media /= 5.0;
    printf("Média das notas: %.2f\n", media);

    // system("PAUSE");
    return 0;
}
