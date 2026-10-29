/* Prog21.c */
/* Mostra o uso de strcmp() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char resposta[]="BRANCO";
    char resp[40];

    printf("Qual é a cor do cavalo branco de Napoleão?");
    gets(resp);

    while (strcmp(resp,resposta) != 0)
    {
        printf("Resposta errada. Tente de novo.\n");
        gets(resp);
    }
    printf("Correto!\n");
    // system("PAUSE");
    return 0;
}
