/*
 * ID: A05-08-P17
 * Aula: ../../atividades/aulas-06-e-07.md
 * Objetivo: Movimenta uma imagem na tela utilizando ponteiros e matrizes.
 */
/* Prog17.c */
/* movimenta imagem na tela */
#include <stdio.h>
#include <stdlib.h>
#include "../entrada_segura.h"
#define LIN 10
#define COL 5

int main(void)
{
    int cont, j, k;
    char linha[8];
    char *ptr[LIN];
    char *temp;

    static char foguet[LIN][COL] =
    {
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0},
        { 0, 0, '^' , 0, 0} ,
        { 0, '^','#', '^',0 }
    };

    static char terra[]=
    { '=' ,'=', '=' ,'=' ,'=' ,'\0'};

    for(cont=0; cont<LIN; cont++)
        *(ptr+cont)=*(foguet+cont);
    for(cont=0; cont<LIN-1; cont++)
    {
        for(j=0; j<LIN ; j++)
        {
            for(k=0; k<COL; k++)
                printf("%c", *(*(ptr+j)+k));/* ptr[j][k] */
            printf("\n");
        }
        printf("%s\n",terra);
        /* Avança por linha, sem depender de conio.h nem executar "cls". */
        if (!ler_linha(linha, sizeof linha)) return 0;
        putchar('\n');
        temp=*ptr;
        for(j=0; j<LIN-1; j++)
            *(ptr+j) = *(ptr+j+1);
        *(ptr+LIN-1)=temp;
    }
    // system("pause");
    return 0;
}
