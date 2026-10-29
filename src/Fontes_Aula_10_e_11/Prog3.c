/* Prog3.c */
/* Lê um caractere por vez de um arquivo */
#include <stdio.h> /* define FILE */
#include <stdlib.h>

int main(void)
{
    FILE *fptr;  /* ponteiro para arquivo */
    short int ch;

    if( (fptr = fopen("ArqText.txt","r")) == NULL)
    {
        puts("Não foi possível abrir o arquivo");
        exit(1);
    }

    while((ch=fgetc(fptr)) != EOF)  /*Lê um caractere do arquivo */
        printf("%c",ch);          /*imprime o caractere no vídeo */
    fclose(fptr);

    return 0;
}
