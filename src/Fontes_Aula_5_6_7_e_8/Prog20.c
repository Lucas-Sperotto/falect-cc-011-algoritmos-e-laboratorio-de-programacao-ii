/*
 * ID: A05-08-P20
 * Aula: ../../aulas/aula-07/README.md
 * Objetivo: Mostra o uso de um vetor de ponteiros para funções.
 */
/* Prog20.c */
/* Mostra uma matriz de ponteiros para função */
#include <stdio.h>
#include <stdlib.h>

const int true=1;

void func0(void), func1(void), func2(void);/* Protótipos */

int main(void)
{
    void (*ptrf[3])(void);/* Matriz de ponteiros para funções */

    ptrf[0] = func0;
    ptrf[1] = func1;
    ptrf[2] = func2;

    do
    {
        int i;
        printf("0 - ABRIR\n");
        printf("1 - FECHAR\n");
        printf("2 - SALVAR\n");
        printf("\nEscolha um item: ");
        if (scanf("%d", &i) != 1) return 1;
        if(i < 0 || i > 2) break;

        (*ptrf[i])(); /* Chama função */
    }
    while(true);
    // system("PAUSE");
    return 0;
}

void func0()
{
    printf("\n*** Estou em func0() ***\n");
}

void func1()
{
    printf("\n*** Estou em func1() ***\n");
}

void func2()
{
    printf("\n*** Estou em func2() ***\n");
}
