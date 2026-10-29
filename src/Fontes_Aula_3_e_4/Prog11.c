/* Prog11.c */
/* Mostra o uso do operador sizeof() */
#include <stdio.h>
#include <stdlib.h>

union Numero
{
    char str[32];
    int i;
    float f;
} x; /* Cria variável */

int main(void)
{
    printf("%d\n", sizeof(union Numero));
    printf("%d\n", sizeof(x));

    system("PAUSE");
    return 0;
}
