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
    printf("Endereço de i  = %08X\n" , &exemplo.i );
    printf("Endereço de f  = %08X\n" , &exemplo.f );
    printf("Endereço de d  = %08X\n" , &exemplo.d );
    printf("Endereço de x  = %08X\n" , &exemplo   );

    system("PAUSE");
    return 0;
}
