/* Prog2.c */
/* Mostra o uso de ponteiros variáveis */
#include <stdio.h>
#include <stdlib.h>

void reajusta20( float *, float *); /* protótipo */

int main()
{
    float val_preco, val_reaj;
    do
    {
        printf("\nInsira o preço atual: ");
        scanf("%f", &val_preco);
        reajusta20(&val_preco, &val_reaj); /* Enviando endereços */
        printf("\nO preço novo é %.2f\n", val_preco);
        printf("O aumento foi de %.2f\n", val_reaj);
    }
    while( val_preco != 0.0);

    // system("PAUSE");
    return 0;
}

/* reajusta20() */
/* Reajusta o preço em 20% */
void reajusta20(float *preco, float *reajuste) /* Recebendo ponteiros */
{
    *reajuste = *preco * 0.2;
    *preco *= 1.2;
}

