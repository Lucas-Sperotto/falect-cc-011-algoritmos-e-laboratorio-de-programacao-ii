/* Prog2.c */
/* Lê um caractere por vez de um arquivo */
#include <stdio.h> /* define FILE */
#include <stdlib.h>

int main(void)
{
    FILE *fptr;  /* ponteiro para arquivo */
    short int ch;

    fptr = fopen("ArqText.txt","r");/*abre arq. p/ ler em modo texto*/

    while((ch=fgetc(fptr)) != EOF)  /*Lê um caractere do arquivo */
        printf("%c",ch);          /*imprime o caractere no vídeo */
    fclose(fptr);

    return 0;
}
