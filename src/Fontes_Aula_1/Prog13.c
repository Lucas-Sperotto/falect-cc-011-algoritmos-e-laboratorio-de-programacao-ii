/* Prog13.c */
/* Mostra o uso de strings */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[80];
    printf("Digite o seu nome: ");
    scanf("%s", nome);
    printf("Saudações %s.\n", nome);
    system("PAUSE");
    return 0;
}
