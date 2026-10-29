/* Prog17.c */
/* Mostra o uso da aritmética com endereços */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char salute[]="Saudações, ";
    char nome[80];
    printf("Digite o seu nome: ");
    gets(nome);
    printf("%s%s\n", salute, nome + 5);
    system("PAUSE");
    return 0;
}
