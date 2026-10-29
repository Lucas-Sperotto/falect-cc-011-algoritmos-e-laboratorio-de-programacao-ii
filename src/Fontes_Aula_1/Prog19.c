/* Prog19.c */
/* Mostra o uso de strcat() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char salute[100]="Saudações, ";
    char nome[80];

    printf("Digite o seu nome: ");
    gets(nome);

    strcat(salute, nome);

    printf("%s\n", salute);

    system("PAUSE");
    return 0;
}
