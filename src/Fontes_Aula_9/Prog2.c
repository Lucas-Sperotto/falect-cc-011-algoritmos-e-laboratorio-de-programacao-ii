/* Prog2.c */
#include <stdio.h>
#include <stdlib.h>

int palavra()
{
    unsigned int n = ~0; /* todos os bits ligados */
    int i;
    for(i = 0; n ; i++) /* enquanto n não for zero */
        n <<= 1;
    return i;
}

int main()
{
    int t = palavra();
    printf("O tamanho da palavra dessa máquina é %d bits.\n", t);
    // system("pause");
    return 0;
}



