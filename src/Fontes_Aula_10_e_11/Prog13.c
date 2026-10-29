/*
 * ID: A10-11-P13
 * Aula: ../../atividades/aula-11.md
 * Objetivo: Lê estruturas de dados armazenadas em um arquivo binário.
 */
/* Prog13.c — lê estruturas do disco. */
#include <stdio.h>
#include <stdlib.h>

/* Formato didático nativo: padding, endian e tamanhos dependem da ABI.
 * Leia somente arquivos gerados por estes exemplos na mesma plataforma. */
typedef struct Livro {
    char Titulo[50];
    char Autor[50];
    short NumReg;
    double Preco;
} Livro;

void PrintLivro(Livro livro)
{
    /* Não confiar em terminadores presentes num arquivo externo. */
    livro.Titulo[sizeof livro.Titulo - 1] = '\0';
    livro.Autor[sizeof livro.Autor - 1] = '\0';
    printf("\n\tTítulo: %s\n", livro.Titulo);
    printf("\tAutor : %s\n", livro.Autor);
    printf("\tNo.Reg: %hd\n", livro.NumReg);
    printf("\tPreço : %.2f\n", livro.Preco);
}

int main(void)
{
    Livro livro;
    size_t lidos;
    int status = 0;
    FILE *fptr = fopen("Livros.Dat", "rb");
    if (fptr == NULL) { perror("Livros.Dat"); return 1; }
    while ((lidos = fread(&livro, 1, sizeof livro, fptr)) == sizeof livro)
        PrintLivro(livro);
    /* Registro parcial não deve ser interpretado como uma estrutura completa. */
    if (lidos != 0 || ferror(fptr)) status = 1;
    if (fclose(fptr) == EOF) status = 1;
    // system("pause");
    return status;
}
