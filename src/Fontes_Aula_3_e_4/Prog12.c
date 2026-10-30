/*
 * ID: A03-04-P12
 * Aula: ../../aulas/aula-04/README.md
 * Objetivo: Mostra o uso do operador de endereço.
 */
/* Prog12.c */
/* Mostra o uso do operador de endereço */
#include <stdio.h>
#include <stdlib.h>

typedef union
{
    int i;
    float f;
    double d;
} Num;

int main(void)
{
    Num exemplo;

    printf("\n\n");
    printf("Endereço de i  = %p\n" , (void *)&exemplo.i );
    printf("Endereço de f  = %p\n" , (void *)&exemplo.f );
    printf("Endereço de d  = %p\n" , (void *)&exemplo.d );
    printf("Endereço de x  = %p\n" , (void *)&exemplo );

    // system("PAUSE");
    return 0;
}
