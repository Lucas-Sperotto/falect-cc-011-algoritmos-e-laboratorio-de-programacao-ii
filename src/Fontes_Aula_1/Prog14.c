/* Prog14.c */
/* Mostra leitura de string com gets() */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[80];
    printf("Digite o seu nome: ");
    gets(nome); /* lê texto do teclado */
    printf("Saudações %s.\n", nome);
    system("PAUSE");
    return 0;
}

