/* Prog1.c */
/* Grava um caractere por vez num arquivo */
#include <stdio.h> /* define FILE */
#include <stdlib.h>
#include <conio.h>

int main(void)
{
    FILE *fptr;  /* ponteiro para arquivo */
    char ch;

    fptr=fopen("ArqText.txt","w");/*abre arq.p/gravar em modo texto */
    while((ch=getche()) != '\r')  /*Lê um caractere do teclado */
        fputc(ch,fptr);         /*grava caractere no arquivo */
    fclose(fptr);

    return 0;
}
