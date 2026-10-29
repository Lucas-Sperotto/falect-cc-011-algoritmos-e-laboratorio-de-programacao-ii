/* Prog18.c */
/* Mostra o uso de strlen() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int len, i;
    char nome[80];

    printf("Digite o seu nome: ");
    gets(nome);

    len=strlen(nome);

    for(i=0; i<len + 4; i++)
        printf("Endereço = %u\tChar  = %c\tDec   = %d\n",
               (unsigned)(nome+i), nome[i], (int)nome[i]);

    // system("PAUSE");
    return 0;
}
