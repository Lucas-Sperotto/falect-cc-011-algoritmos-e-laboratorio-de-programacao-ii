/* Prog13.c */
/* Lê estruturas do disco */
#include <stdio.h> /* define FILE */
#include <stdlib.h>
#include <conio.h> /* Para getch() */

typedef struct Livro
{
    char Titulo[50];
    char Autor[50];
    short NumReg;
    double Preco;
} Livro;

void PrintLivro(Livro livro)
{
    printf("\n\tTítulo: %s\n", livro.Titulo);
    printf("\tAutor : %s\n", livro.Autor);
    printf("\tNo.Reg: %hd\n", livro.NumReg);
    printf("\tPreço : %.2lf\n", livro.Preco );
}

int main()
{
    Livro livro;
    char resp;
    FILE *fptr; /* ponteiro para arquivo */

    if((fptr = fopen("Livros.Dat","rb"))==NULL) exit(1);

    while(fread(&livro, sizeof(Livro),1,fptr)==1) PrintLivro(livro);

    fclose(fptr);
    system("pause");
    return 0;
}
