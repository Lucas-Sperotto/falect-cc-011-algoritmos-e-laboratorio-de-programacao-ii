/*
 * ID: A10-11-P15
 * Aula: ../../aulas/aula-11/README.md
 * Objetivo: Mostra o uso das funções fseek() e ftell() para posicionamento e acesso a registros em arquivos.
 */
/* Prog15.c — fseek/ftell e acesso ao registro solicitado. */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../entrada_segura.h"

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
    char linha[80], *fim;
    long nrec, rec, tamanho, posicao;
    int status = 0;
    FILE *fptr = fopen("Livros.Dat", "rb");
    if (fptr == NULL) { perror("Livros.Dat"); return 1; }
    if (fseek(fptr, 0, SEEK_END) != 0 || (tamanho = ftell(fptr)) < 0 ||
        tamanho % (long)sizeof livro != 0) {
        fclose(fptr); return 1;
    }
    nrec = tamanho / (long)sizeof livro;
    printf("O número de registros é %ld\n", nrec);
    puts("Insira o número do registro: ");
    if (!ler_linha(linha, sizeof linha)) { fclose(fptr); return 1; }
    errno = 0;
    rec = strtol(linha, &fim, 10);
    if (fim == linha || *fim != '\0' || errno || rec <= 0 || rec > nrec) {
        puts("Registro não existe"); status = 1;
    } else {
        /* rec identifica o registro pedido; nrec é apenas a quantidade total. */
        posicao = (rec - 1) * (long)sizeof livro;
        if (fseek(fptr, posicao, SEEK_SET) != 0 ||
            fread(&livro, sizeof livro, 1, fptr) != 1) status = 1;
        else PrintLivro(livro);
    }
    if (fclose(fptr) == EOF) status = 1;
    // system("pause");
    return status;
}
