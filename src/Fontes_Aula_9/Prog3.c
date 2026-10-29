/* Prog3.c */
/* Converte hexa para binario */
#include <stdio.h>
#include <stdlib.h>
#include <math.h> /* para pow() */

int palavra();

int main()
{
    int t, j, num, bit;
    unsigned int mask;
    while(1)
    {
        t = palavra();

        /* um no bit mais significativo e zero nos outros */
        mask = pow(2, t-1);

        printf("\nDigite um número em hexadecimal: ");
        scanf("%x",&num) ;
        printf("Binário de %04x é: ", num);

        for(j=0; j<t ; j++)
        {
            bit = (mask & num) ? 1 : 0;
            printf("%d",bit);
            if(((j + 1) % 8) == 0) /* imprime traco entre bytes */
                printf("--");
            mask >>= 1;
        }
    }
    // system("pause");
    return 0;
}

int palavra()
{
    unsigned int n = ~0; /* todos os bits ligados */
    int i;
    for(i = 0; n ; i++) /* enquanto n não for zero */
        n <<= 1;
    return i;
}
