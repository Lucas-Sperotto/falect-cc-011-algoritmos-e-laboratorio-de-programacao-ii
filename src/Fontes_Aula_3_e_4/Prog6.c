/*
 * ID: A03-04-P06
 * Aula: ../../aulas/aula-04/README.md
 * Objetivo: Mostra o uso de enumerações.
 */
#include <stdio.h>
/* Mostra o uso de enumerações */
enum Mes {Jan = 1, Fev, Mar, Abr, Mai, Jun, Jul, Ago, Set, Out,
          Nov, Dez
         };

int main(void)
{
    enum Mes m1, m2, m3; /*Cria variáveis do tipo enum Mes */

    m1 = Abr; /*Atribui valores */
    m2 = Jun; /*Atribui valores */

    m3 = m2 - m1; /*Operações aritméticas permitidas */
    printf("Diferença entre os meses: %d\n", m3);
    if (m1 < m2) /*Comparações permitidas */
    {
        printf("Primeiro Mês é menor que o Segundo Mês");
    }
    else
    {
        printf("Segundo Mês é menor que o Primeiro Mês");
    }
    return 0;
}

