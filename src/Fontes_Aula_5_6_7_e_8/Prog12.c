/*
 * ID: A05-08-P12
 * Aula: ../../atividades/aulas-05-e-06.md
 * Objetivo: Procura um caractere em uma string utilizando ponteiros.
 */
/* Prog12.c */
/* Procura um caractere numa cadeia de caracteres */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"

char * procura(char *, char );/* protótipo */

int main(void)
{
    char str[81], *ptr;

    printf("Digite uma frase:\n");
    if (!ler_linha(str, sizeof str)) return 1;

    ptr = procura(str, 'h');

    printf("\nA frase começa no endereço %p\n", (void *)str);

    if(ptr)
    {
        printf("\nPrimeira ocorrência do caractere 'h': %p\n", (void *)ptr);
        printf( "\nA sua posição é: %td\n", ptr-str);
    }
    else
        printf( "O caractere 'h' não existe nesta frase.\n");

    // system("PAUSE");
    return 0;
}

/* Procura um caractere numa frase */
char *procura(char *s, char ch)
{
    while( *s != ch && *s != '\0') s++;
    if(*s != '\0') return s;
    return (char *)0;
}
