/* Prog3.c */
/* Mostra estruturas aninhadas */
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int dia;
    char mes[10];
    int ano;
} Data;

typedef struct
{
    int pecas;
    float preco;
    Data diavenda;
} Venda;

int main()
{
    static Venda A = { 20, 110.0, {7,"Novembro",2001} };

    printf("Peças: %d\n", A.pecas);
    printf("Preço: %d\n", A.preco);
    printf("Data : %d de %s de %d\n",
           A.diavenda.dia, A.diavenda.mes, A.diavenda.ano);
    // system("PAUSE");
    return 0;
}
