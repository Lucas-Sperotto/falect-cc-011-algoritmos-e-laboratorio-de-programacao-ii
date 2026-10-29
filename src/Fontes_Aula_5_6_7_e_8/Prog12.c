/* Prog12.c */
/* Procura um caractere numa cadeia de caracteres */
#include <stdio.h>
#include <stdlib.h>

char * procura(char *, char );/* protótipo */

int main()
{
    char str[81], *ptr;

    printf("Digite uma frase:\n");
    gets(str);

    ptr = procura(str, 'h');

    printf("\nA frase começa no endereço %p\n", str);

    if(ptr)
    {
        printf("\nPrimeira ocorrência do caractere 'h': %p\n", ptr);
        printf( "\nA sua posição é: %d\n", ptr-str);
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
