/* Prog19.c */
/* Mostra o uso de ponteiro como argumento de função */
#include <stdio.h>
#include <stdlib.h>

void func( char * (*)(char *));

int main()
{
    char * (*p)(char *);
    p = gets;
    func(p);

    system("PAUSE");
    return 0;
}

void func(char * (*p)(char *))
{
    char nome[80];

    printf("Digite seu nome: ");

    (*p)(nome);	/* chama a função gets()*/

    printf("Seu nome é: %s\n", nome);
}
