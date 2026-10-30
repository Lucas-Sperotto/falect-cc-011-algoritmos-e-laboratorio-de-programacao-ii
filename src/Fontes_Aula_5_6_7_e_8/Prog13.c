/*
 * ID: A05-08-P13
 * Aula: ../../aulas/aula-06/README.md
 * Objetivo: Implementa funções para manipulação de strings utilizando ponteiros.
 */
/* Prog13.c */
/* Funções para Manipular Strings */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"

/* Protótipos */
int tamanho_string(char *);
void copia_string(char *, char *);
int compara_string(char *, char *);

int main(void)
{
    int len, i;
    char nome[80];
    char str[] = "Carrta";
    char resposta[]="BRANCO";
    char resp[40];

    printf("Digite o seu nome: ");
    if (!ler_linha(nome, sizeof nome)) return 1;
    len=tamanho_string(nome);
    for(i=0; i<=len; i++)
        printf("Endereço = %p\tChar  = %c\tDec   = %d\n",
               (void *)(nome+i), nome[i], (int)nome[i]);

    printf("\n\n%s\n", str);
    copia_string(str+2, str+3); /* Rotina própria: copia para a esquerda, inclusive com sobreposição.
                            * A strcpy() da biblioteca não admite sobreposição. */
    printf("%s\n\n", str);

    printf("\nQual é a cor do cavalo branco de Napoleão?");
    if (!ler_linha(resp, sizeof resp)) return 1;

    while (compara_string(resp,resposta) != 0)
    {
        printf("Resposta errada. Tente de novo.\n");
        if (!ler_linha(resp, sizeof resp)) return 1;
    }
    printf("Correto!\n");
    return 0;

}

/* Retorna o tamanho da cadeia */
int tamanho_string(char *s)
{
    int i = 0;
    while (*(s++)) i++;
    return i;
}

/* Copia a cadeia origem na cadeia destino */
void copia_string(char *dest, char *orig)
{
    while ((*(dest++) = *(orig++)) != '\0')
        ;
}

/* Compara a cadeia s com a cadeia t
*  Retorna a diferença ASCII:
*       um número positivo se s > t
*       um número negativo se s < t
*       zero se s == t
*/
int compara_string(char *s, char *t)
{
    while(*s == *t && *s)
    {
        s++;
        t++;
    }
    return (unsigned char)*s - (unsigned char)*t;
}
