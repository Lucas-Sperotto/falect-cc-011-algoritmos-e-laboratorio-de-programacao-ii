/*
 * ID: A05-08-P06
 * Aula: ../../aulas/aula-05/README.md
 * Objetivo: Mostra a inicialização do ponteiro.
 */
/* Prog6.c */
/* Mostra a inicialização do ponteiro */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x,y;
    int *px = &x;	/* Inicializa px com o endereço de x */

    *px = 14;	/* O mesmo que x = 14 */
    y = *px;	/* O mesmo que y = x  */

    printf("y = %d\n", y);

    // system("PAUSE");
    return 0;
}

