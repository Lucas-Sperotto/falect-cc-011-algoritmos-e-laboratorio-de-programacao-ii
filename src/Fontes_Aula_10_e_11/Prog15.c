/* Prog15.c */
/* Mostra o uso de fseek() e ftell() */
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
    long nrec, rec, posicao;

    if((fptr = fopen("Livros.Dat","rb"))==NULL) exit(1);

    fseek(fptr,0,2);

    nrec = ftell(fptr)/sizeof(Livro);
    printf("O número de registros é %ld\n", nrec);

    puts("Insira o número do registro: ");
    scanf("%ld", &rec);
    if(rec > 0 && rec <= nrec)
    {
        posicao = (nrec-1) * sizeof(Livro);
        fseek(fptr,posicao,0);/* Posiciona no registro desejado */
        fread(&livro, sizeof(Livro),1,fptr);
        PrintLivro(livro);
        fclose(fptr);
    }
    else
        puts("Registro não existe");

    // system("pause");
    return 0;
}
