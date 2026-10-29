/* Prog13.c */
/* Funções para Manipular Strings */
#include <stdio.h>
#include <stdlib.h>

/* Protótipos */
int strlen(char *);
void strcpy(char *, char *);
int strcmp(char *, char *);

int main()
{
    int len, i;
    char nome[80];
    char str[] = "Carrta";
    char resposta[]="BRANCO";
    char resp[40];

    printf("Digite o seu nome: ");
    gets(nome);
    len=strlen(nome);
    for(i=0; i<len + 4; i++)
        printf("Endereço = %u\tChar  = %c\tDec   = %d\n",
               (unsigned)(nome+i), nome[i], (int)nome[i]);

    printf("\n\n%s\n", str);
    strcpy(str+2, str+3); // apaga um caractere da cadeia
    printf("%s\n\n", str);

    printf("\nQual é a cor do cavalo branco de Napoleão?");
    gets(resp);

    while (strcmp(resp,resposta) != 0)
    {
        printf("Resposta errada. Tente de novo.\n");
        gets(resp);
    }
    printf("Correto!\n");
    return 0;

}

/* Retorna o tamanho da cadeia */
int strlen(char *s)
{
    int i = 0;
    while (*(s++)) i++;
    return i;
}

/* Copia a cadeia origem na cadeia destino */
void strcpy(char *dest, char *orig)
{
    while (*(dest++) = *(orig++));
}

/* Compara a cadeia s com a cadeia t
*  Retorna a diferença ASCII:
*       um número positivo se s > t
*       um número negativo se s < t
*       zero se s == t
*/
int strcmp(char *s, char *t)
{
    while(*s == *t && *s)
    {
        s++;
        t++;
    }
    return *s - *t;
}
