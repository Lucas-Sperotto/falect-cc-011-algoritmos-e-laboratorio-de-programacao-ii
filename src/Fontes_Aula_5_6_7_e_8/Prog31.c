/* Prog30.c */
/* Mostra a implementação de uma lista ligada */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> /* para getch() */

typedef struct Livro
{
    char Titulo[30];
    char Autor[30];
    int  NumReg;
    double Preco;
    struct Livro *Proximo;
} Livro;

Livro *primeiro, *atual, *NovoLivro;

void GetLivro()
{
    char temp[80];
    NovoLivro = (Livro *)malloc(sizeof(Livro));
    if( primeiro == (Livro *)NULL)
        primeiro = atual = NovoLivro;
    else
    {
        atual = primeiro;
        while( atual->Proximo != (Livro *)NULL)
            atual = atual->Proximo;/* procura novo item */
        atual->Proximo = NovoLivro;
        atual = NovoLivro;
    }
    printf("Digite titulo: ");
    gets(atual->Titulo);
    printf("Digite autor: ");
    gets(atual->Autor);
    printf("Digite o número do registro: ");
    gets(temp);
    atual->NumReg = atoi(temp);
    printf("Digite o preço: ");
    gets(temp);
    atual->Preco = atof(temp);
    atual->Proximo=(Livro *)NULL;
}

void PrintLivro()
{
    if( primeiro == (Livro *)NULL)
    {
        puts("Lista vazia");
        return;
    }

    atual = primeiro;

    do
    {
        printf( "Título: %s\n", atual->Titulo);
        printf( "Autor : %s\n" , atual->Autor);
        printf( "No.Reg: %d\n" , atual->NumReg);
        printf( "Preço : %.2f\n\n" , atual->Preco);
        atual = atual->Proximo;
    }
    while(atual != NULL);
}

int main()
{
    char ch;
    primeiro = (Livro *) NULL; /* sem dados ainda */

    do
    {
        GetLivro();
        puts("\nInserir outro livro (s/n)? ");
        ch = getch();
    }
    while( (ch != 'n') && (ch != 'N'));

    puts("\nLISTA DOS LIVROS CADASTRADOS");
    puts("============================");

    PrintLivro();

    system("PAUSE");
    return 0;
}
