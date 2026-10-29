/* Prog4.c */
/* Mostra passagem de estruturas para funções por valor */
/* Mostra uma função que retorna uma estrutura */
#include <stdio.h>
#include <stdlib.h>

typedef struct Venda
{
    int pecas;
    float preco;
} Venda;

Venda TotalVendas( Venda C, Venda D);/* Protótipo */

int main()
{
    Venda A, B, Total;

    printf("Venda A\n=======\n");
    printf("Insira o número de peças: ");
    scanf("%d", &A.pecas);
    printf("Insira o preço: ");
    scanf("%f", &A.preco);

    printf("\nVenda B\n=======\n");
    printf("Insira o número de peças: ");
    scanf("%d", &B.pecas);
    printf("Insira o preço: ");
    scanf("%f", &B.preco);
    Total = TotalVendas( A,B);/* Estruturas como argumento e retorno */

    printf("\n\nVenda Total\n===========");
    printf("\nTotal de peças: %d." , Total.pecas );
    printf("\nPreço total   : %.2f\n" , Total.preco );

    system("PAUSE");
    return 0;
}

Venda TotalVendas(Venda C, Venda D)
{
    Venda T;
    T.pecas = C.pecas + D.pecas;
    T.preco = C.preco + D.preco;
    return T;
}
