/* Prog22.c */
/* Mostra uma matriz de ponteiros para função */
#include <stdio.h>
#include <stdlib.h>
void func0(void), func1(void), func2(void);/* Protótipos */

const true=1;

typedef void (*PFunc)(void); /* O tipo PFunc é ponteiro p/fção void */

int main()
{
    PFunc ptrf[3] = { func0, func1, func2};/* Matriz inicializada */

    do
    {
        int i;
        printf("0 - ABRIR\n");
        printf("1 - FECHAR\n");
        printf("2 - SALVAR\n");
        printf("\nEscolha um item: ");
        scanf("%d", &i);
        if(i < 0 || i > 2) break;

        (*ptrf[i])(); /* Chama função */
    }
    while(true);
    system("PAUSE");
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
