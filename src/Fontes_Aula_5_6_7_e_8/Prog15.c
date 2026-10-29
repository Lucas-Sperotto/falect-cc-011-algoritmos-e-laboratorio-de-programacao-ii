/* Prog15.c */
/* Imprime o dia da semana a partir de uma data */
/* Mostra o uso de uma matriz de ponteiros */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>	/* para getche() */

int dsemana(int, int, int); /*Protótipo */

int main()
{
    static char *diasemana[7]=
    {
        "Domingo",
        "Segunda-feira",
        "Terça-feira",
        "Quarta-feira",
        "Quinta-feira",
        "Sexta-feira",
        "Sábado"
    };
    int dia, mes, ano;
    const char ESC = 27;
    do
    {
        printf("Digite a data na forma dd mm aaaa: ");
        scanf("%d%d%d", &dia, &mes, &ano);
        printf("%s\n", diasemana [ dsemana(dia,mes,ano)] );
        printf("ESC para terminar ou ENTER para recomeçar\n");
    }
    while (getch() != ESC);

    // system("PAUSE");
    return 0;
}

/* Encontra o dia da semana a partir de uma data
 * Retorna 0 para domingo, 1 para segunda-feira etc.
 */
int dsemana(int dia, int mes, int ano)
{
    int dSemana = ano + dia + 3 * (mes - 1) - 1;
    if( mes < 3)
        ano--;
    else
        dSemana -= (int)(0.4*mes+2.3);
    dSemana += (int)(ano/4) - (int)((ano/100 + 1)*0.75);
    dSemana %= 7;
    return dSemana;
}
