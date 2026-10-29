/* Prog20.c */
/* Mostra a comparação entre strings */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char resposta[]="BRANCO";
    char resp[40];

    printf("Qual é a cor do cavalo branco de Napoleão?");
    gets(resp);

    while (resp != resposta)
    {
        printf("Resposta errada. Tente de novo.\n");
        gets(resp);
    }
    printf("Correto!\n");
    system("PAUSE");
    return 0;
}

