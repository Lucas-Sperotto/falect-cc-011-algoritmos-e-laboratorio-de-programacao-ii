/* Prog6.c */
/* Grava dados formatados num arquivo */
#include <stdio.h> /* define FILE */
#include <stdlib.h>
#include <string.h>
#define TRUE 1

int main(void)
{
    FILE *fptr; /* ponteiro para arquivo */
    char titulo[30];
    int regnum;
    double preco;
    fptr = fopen("Livros.txt","w");
    while (TRUE)
    {
        printf("\nDigite titulo, registro e preco do livro: ");
        scanf("%s %d %lf",titulo,&regnum,&preco);
        if(strlen(titulo) <= 1) break;
        fprintf(fptr,"%s %d %.2lf\n",titulo,regnum,preco);
    }

    fclose(fptr);
    // system("pause");
    return 0;
}
