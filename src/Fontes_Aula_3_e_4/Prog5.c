/*
 * ID: A03-04-P05
 * Aula: ../../atividades/aulas-03-e-04.md
 * Objetivo: Mostra uma matriz de estruturas.
 */
/* Prog5.c */
/* Mostra uma matriz de estruturas */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../entrada_segura.h"

#define ESC 27
#define TRUE 1

typedef struct
{
    int dia;
    char mes[10];
    int ano;
} Data;

typedef struct
{
    Data diavenda;
    int pecas;
    float preco;
} Venda;

void listavenda(void);
void novavenda(void);

Venda vendas[50];
Venda Total = {{0, "", 0}, 0, 0.0};
int n = 0;

int main(void)
{
    char opcao[80];
    while (TRUE)
    {
        printf("Digite E para entrar uma venda\n");
        printf("       L para listar as vendas\n");
        printf("       ESC ou Q para terminar (confirme com Enter)\n");
        /* getche() era específico de conio.h. Agora a opção é uma linha. */
        if (!ler_linha(opcao, sizeof opcao))
            break;
        switch (opcao[0])
        {
        case 'E': novavenda(); break;
        case 'L': listavenda(); break;
        case ESC:
        case 'Q': return 0;
        default: printf("Opção inválida!\n"); break;
        }
    }
    // system("PAUSE");
    return 0;
}

void novavenda(void)
{
    char temp[80];
    Venda nova;
    if (n >= 50)
    {
        puts("Limite de 50 vendas atingido.");
        return;
    }
    /* gets() não limitava as strings. Só adiciona uma venda completa. */
    printf("Dia: ");
    if (!ler_linha(temp, sizeof temp) || sscanf(temp, "%d", &nova.diavenda.dia) != 1)
        return;
    printf("Mês: ");
    if (!ler_linha(nova.diavenda.mes, sizeof nova.diavenda.mes))
        return;
    printf("Ano: ");
    if (!ler_linha(temp, sizeof temp) || sscanf(temp, "%d", &nova.diavenda.ano) != 1)
        return;
    printf("Peças: ");
    if (!ler_linha(temp, sizeof temp) || sscanf(temp, "%d", &nova.pecas) != 1 ||
        nova.pecas < 0 || nova.pecas > 1000000)
        return;
    printf("Preço: ");
    if (!ler_linha(temp, sizeof temp) || sscanf(temp, "%f", &nova.preco) != 1 ||
        !isfinite(nova.preco) || nova.preco < 0.0f || nova.preco > 1000000000.0f)
        return;
    vendas[n++] = nova;
    Total.pecas += nova.pecas;
    Total.preco += nova.preco;
}

void listavenda(void)
{
    int i;
    if (!n)
    {
        printf("Lista vazia.\n");
        return;
    }
    printf("\n\nRelatório\n");
    for (i = 0; i < n; i++)
    {
        printf("%2d de %10s de %4d", vendas[i].diavenda.dia,
               vendas[i].diavenda.mes, vendas[i].diavenda.ano);
        printf("%10d%20.2f\n", vendas[i].pecas, vendas[i].preco);
    }
    printf("\nTotal%29d%20.2f\n\n", Total.pecas, Total.preco);
}
