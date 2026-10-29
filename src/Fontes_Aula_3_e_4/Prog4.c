/*
 * ID: A03-04-P04
 * Aula: ../../atividades/aulas-03-e-04.md
 * Objetivo: Mostra passagem de estruturas para funções por valor; mostra uma função que retorna uma estrutura.
 */
/* Prog4.c */
/* Mostra passagem de estruturas para funções por valor */
/* Mostra uma função que retorna uma estrutura */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Venda
{
    int pecas;
    float preco;
} Venda;

Venda TotalVendas( Venda C, Venda D);/* Protótipo */

int main(void)
{
    Venda A, B, Total;

    printf("Venda A\n=======\n");
    printf("Insira o número de peças: ");
    if (scanf("%d", &A.pecas) != 1) {
        fputs("Entrada inválida.\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Insira o preço: ");
    if (scanf("%f", &A.preco) != 1) {
        fputs("Entrada inválida.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("\nVenda B\n=======\n");
    printf("Insira o número de peças: ");
    if (scanf("%d", &B.pecas) != 1) {
        fputs("Entrada inválida.\n", stderr);
        return EXIT_FAILURE;
    }
    printf("Insira o preço: ");
    if (scanf("%f", &B.preco) != 1) {
        fputs("Entrada inválida.\n", stderr);
        return EXIT_FAILURE;
    }
    /* Limita o domínio para impedir overflow na soma das peças. */
    if (A.pecas < 0 || A.pecas > 1000000 ||
        B.pecas < 0 || B.pecas > 1000000)
        return EXIT_FAILURE;
    /* Preços no domínio didático evitam overflow do total em float. */
    if (!isfinite(A.preco) || !isfinite(B.preco) ||
        A.preco < 0.0f || A.preco > 1000000000.0f ||
        B.preco < 0.0f || B.preco > 1000000000.0f)
        return EXIT_FAILURE;
    Total = TotalVendas( A,B);/* Estruturas como argumento e retorno */

    printf("\n\nVenda Total\n===========");
    printf("\nTotal de peças: %d." , Total.pecas );
    printf("\nPreço total   : %.2f\n" , Total.preco );

    // system("PAUSE");
    return 0;
}

Venda TotalVendas(Venda C, Venda D)
{
    Venda T;
    T.pecas = C.pecas + D.pecas;
    T.preco = C.preco + D.preco;
    return T;
}
