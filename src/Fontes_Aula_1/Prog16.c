/* Prog16.c */
/* Mostra o uso de strings inicializadas */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char salute[]="Saudações, ";
    char nome[80];
    printf("Digite o seu nome: ");
    gets(nome);
    printf("%s%s\n", salute, nome);
    // system("PAUSE");
    return 0;
}
