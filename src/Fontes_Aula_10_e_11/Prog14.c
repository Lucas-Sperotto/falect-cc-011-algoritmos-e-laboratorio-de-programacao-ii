/* Prog14.c */
/* Grava e lê estruturas em disco */
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

Livro GetLivro()
{
    Livro livro;
    printf("\n\tDigite o título: ");
    gets(livro.Titulo);
    printf("\tDigite o nome do autor: ");
    gets(livro.Autor);
    printf("\tDigite o número do registro: ");
    scanf("%hd",&livro.NumReg);
    printf("\tDigite o preço: ");
    scanf("%lf", &livro.Preco);
    rewind(stdin);
    return livro;
}

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

    /* Abre arquivo para leitura e gravação. Adiciona dados no final*/
    if((fptr = fopen("Livros.Dat","ab+"))==NULL) exit(1);

    do
    {
        livro = GetLivro();
        if(fwrite(&livro,sizeof(Livro),1,fptr)!=1) break;
        printf("Mais um livro (s/n)? ");
        resp = getche();
    }
    while(resp != 'n' && resp != 'N');

    fflush(fptr); /* Esvazia o conteúdo do buffer de saída */
    fseek(fptr,0,0); /*Coloca o ponteiro no início do arquivo */

    puts("\n\nLISTA DE LIVROS DO ARQUIVO");
    puts("==========================");

    while(fread(&livro, sizeof(Livro),1,fptr)==1) PrintLivro(livro);
    fclose(fptr);
    // system("pause");
    return 0;
}
