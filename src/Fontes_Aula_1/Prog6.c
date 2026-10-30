/*
 * ID: A01-P06
 * Aula: ../../aulas/aula-01/README.md
 * Objetivo: Imprime o número de dias do ano até uma data especificada.
 */
/* NumDias.C */
/* Imprime o número de dias do ano até a data especificada */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int dmes[12]= { 31,28,31,30,31,30,31,31,30,31,30,31};

    int dia, mes, ano, total, i;

    printf("Digite a data no formato DD/MM/AAAA: ");

    /* %*c lê caractere do teclado e não atribui a nada */
    if (scanf("%d%*c%d%*c%d", &dia, &mes, &ano) != 3 ||
        ano < 1 || ano > 9999 || mes < 1 || mes > 12) {
        fputs("Data inválida.\n", stderr);
        return 1;
    }

    if( ((!(ano%4) && ano%100)) || !(ano%400))
        dmes[1]=29; 	/* Ano bissexto */

    if (dia < 1 || dia > dmes[mes-1]) {
        fputs("Data inválida.\n", stderr);
        return 1;
    }
    total=dia;

    for(i=0; i < mes-1; i++)
        total+=dmes[i];

    printf("Total de dias transcorridos desde o início do ano: %d\n",
           total);

    // system("PAUSE");
    return 0;
}

