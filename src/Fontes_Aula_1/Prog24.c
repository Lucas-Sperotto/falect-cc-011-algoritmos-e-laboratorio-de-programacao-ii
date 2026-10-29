/*
 * ID: A01-P24
 * Aula: ../../atividades/aula-02.md
 * Objetivo: Imprime o dia da semana a partir de uma data.
 */
/* Prog24.c */
/* Imprime o dia da semana a partir de uma data */
/* Mostra o uso de uma matriz de strings */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Histórico: conio.h/getch() são específicos de outros ambientes.
 * A alternativa ISO C lê ESC seguido de ENTER, ou somente ENTER. */

int dsemana(int, int, int); /*Protótipo */

int main(void)
{
    char diasemana[7][14]= {	"Domingo",
                                "Segunda-feira",
                                "Terça-feira",
                                "Quarta-feira",
                                "Quinta-feira",
                                "Sexta-feira",
                                "Sábado"
                           };
    int dia, mes, ano, opcao, ch;
    int dmes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    const char ESC = 27;
    do
    {
        printf("Digite a data na forma dd mm aaaa: ");
        if (scanf("%d%d%d", &dia, &mes, &ano) != 3 ||
            ano < 1 || ano > 9999 || mes < 1 || mes > 12) {
            fputs("Data inválida.\n", stderr);
            return 1;
        }
        dmes[1] = (ano%4 == 0 && (ano%100 != 0 || ano%400 == 0)) ? 29 : 28;
        if (dia < 1 || dia > dmes[mes-1]) {
            fputs("Data inválida.\n", stderr);
            return 1;
        }
        printf("%s\n", diasemana [ dsemana(dia,mes,ano)] );
        printf("ESC e ENTER para terminar ou ENTER para recomeçar\n");
        /* Descarta somente o restante da linha da data. */
        while ((ch = getchar()) != '\n' && ch != EOF) {}
        opcao = getchar();
        if (opcao != '\n' && opcao != EOF && opcao != ESC)
            while ((ch = getchar()) != '\n' && ch != EOF) {}
    }
    while (opcao != ESC && opcao != EOF); /* Histórico: getch() != ESC. */

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
