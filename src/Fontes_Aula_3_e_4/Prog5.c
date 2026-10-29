/* Prog5.c */
/* Mostra uma matriz de estruturas */
#include <stdio.h>  /* para gets(), printf(), scanf() */
#include <stdlib.h> /* Para system(), atoi(), atof(), exit() */
#include <conio.h>  /* Para getch() */

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

void listavenda(void); /* Protótipo */
void novavenda(void);  /* Protótipo */

Venda vendas[50]; /* Cria matriz de estruturas */
Venda Total= {{0,"",0},0,0.0}; /* Cria variável do tipo Venda */


int n=0;

int main()
{
    char ch;
    while(TRUE)
    {
        printf("Digite E para entrar uma venda\n");
        printf("       L para listar as vendas\n");
        printf("       ESC para terminar\n");

        ch=getche();
        printf("\n");
        switch(ch)
        {
        case 'E':
            novavenda();
            break;
        case 'L':
            listavenda();
            break;
        case ESC: /* ESC não pode ser declarado com const */
            exit(0);
        default :
            printf("Opcao invalida!!\n");
        }

    }
    // system("PAUSE");
    return 0;
}
void novavenda()
{
    char temp[80];
    printf("Dia: ");
    gets(temp);
    vendas[n].diavenda.dia=atoi(temp);
    printf("Mes: ");
    gets(vendas[n].diavenda.mes);
    printf("Ano: ");
    gets(temp);
    vendas[n].diavenda.ano=atoi(temp);
    printf("Peças: ");
    gets(temp);
    vendas[n].pecas=atoi(temp);
    printf("Preço: ");
    gets(temp);
    vendas[n].preco=atof(temp);
    Total.pecas += vendas[n].pecas;
    Total.preco += vendas[n++].preco;
}

void listavenda()
{
    int i;
    if(!n)
    {
        printf("Lista vazia.\n");
        return;
    }

    printf("\n\nRelatório\n");
    for (i=0; i<n; i++)
    {
        printf("%2d de %10s de %4d", vendas[i].diavenda.dia,
               vendas[i].diavenda.mes, vendas[i].diavenda.ano);
        printf("%10d", vendas[i].pecas);
        printf("%20.2f\n", vendas[i].preco);
    }
    printf("\nTotal");
    printf("%29d", Total.pecas);
    printf("%20.2f\n\n", Total.preco);
}
