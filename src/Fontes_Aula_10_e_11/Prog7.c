/* Prog7.c */
/* Lê dados formatados do arquivo */
#include <stdio.h> /* define FILE */
#include <stdlib.h>

int main(void)
{
    FILE *fptr; /* ponteiro para arquivo */
    char titulo[30];
    int regnum;
    double preco;
    fptr = fopen("Livros.txt","r");

    while ( fscanf(fptr,"%s %d %lf", titulo, &regnum, &preco) != EOF)
        printf("%s %d %.2lf\n", titulo, regnum, preco);

    fclose(fptr);
    system("pause");
    return 0;
}
