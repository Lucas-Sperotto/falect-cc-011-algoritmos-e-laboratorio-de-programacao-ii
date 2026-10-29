/* Prog15.c */
/* Mostra impressão de string com puts() */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nome[80];
    printf("Digite o seu nome: ");
    gets(nome); /* lê texto do teclado */
    puts("Saudacoes, ");/* imprime texto no vídeo */
    puts(nome);
    puts("puts() pula de linha sozinha");
    puts(&nome[4]);
    // system("PAUSE");
    return 0;
}
