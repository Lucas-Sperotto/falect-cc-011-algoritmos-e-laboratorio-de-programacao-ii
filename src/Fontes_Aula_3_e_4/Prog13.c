/*
 * ID: A03-04-P13
 * Aula: ../../atividades/aulas-03-e-04.md
 * Objetivo: Mostra o uso de uniões anônimas.
 */
/*Prog13.c */
/* Mostra o uso de uniões anônimas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* Para strcpy() */

enum DataType { StrType, IntType, FloatType};

typedef struct
{
    enum DataType Tipo;
    union
    {
        char str_valor[30];
        int int_valor;
        float float_valor;
    };
} UniaoLiteral;

void Print(UniaoLiteral);

int main(void)
{
    UniaoLiteral A;
    A.Tipo=StrType;
    strcpy(A.str_valor, "VVB-Treinamento de Pessoal");
    Print(A);
    A.Tipo=FloatType;
    A.float_valor=34.56;
    Print(A);
    A.Tipo=IntType;
    A.int_valor=345;
    Print(A);

    // system("PAUSE");
    return 0;
}
void Print(UniaoLiteral x)
{
    switch(x.Tipo)
    {
    case StrType:
        printf("Str = %s\n",x.str_valor);
        break;
    case IntType:
        printf("Int = %d\n",x.int_valor);
        break;
    case FloatType:
        printf("Float = %.2f\n",x.float_valor);
        break;
    }
}
