/*
 * ID: A05-08-P15
 * Aula: ../../aulas/aula-06/README.md
 * Objetivo: Imprime o dia da semana a partir de uma data utilizando um vetor de ponteiros.
 */
/* Prog15.c */
/* Imprime o dia da semana a partir de uma data */
/* Mostra o uso de uma matriz de ponteiros */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../entrada_segura.h" /* ENTER é confirmado no terminal Linux. */

int dsemana(int, int, int); /*Protótipo */

int main(void)
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
    char linha[80], continuar[8], sobra;
    int diasmes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    do
    {
        printf("Digite a data na forma dd mm aaaa: ");
        if (!ler_linha(linha, sizeof linha) ||
            sscanf(linha, "%9d%9d%9d %c", &dia, &mes, &ano, &sobra) != 3)
            return 1;
        /* Domínio positivo do calendário gregoriano; protege o índice. */
        if (ano < 1 || ano > 9999 || mes < 1 || mes > 12) return 1;
        diasmes[1] = 28 + (ano%4 == 0 && (ano%100 != 0 || ano%400 == 0));
        if (dia < 1 || dia > diasmes[mes-1]) return 1;
        printf("%s\n", diasemana [ dsemana(dia,mes,ano)] );
        printf("ESC para terminar ou ENTER para recomeçar\n");
    }
    while (ler_linha(continuar, sizeof continuar) && continuar[0] != ESC);

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
