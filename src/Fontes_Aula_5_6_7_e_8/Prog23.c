/* Prog23.c */
/* Mostra ponteiros void */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i=5;
    float f=3.2;

    void *pv;	/* Ponteiro genérico */
    pv = &i;	/* Endereço de um int */

    /* não podemos usar o operador indireto com ponteiros void */
    printf("%d\n", *pv); /* ERRO de compilação */

    pv = &f;	/* Endereço de um float */

    /* não podemos usar o operador indireto com ponteiros void */
    printf("%f\n", *pv); /* ERRO de compilação */

    // system("PAUSE");
    return 0;
}

