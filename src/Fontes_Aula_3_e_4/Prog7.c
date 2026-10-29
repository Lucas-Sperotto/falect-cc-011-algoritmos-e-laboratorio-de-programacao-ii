#include <stdio.h>
/* Mostra o uso de enumerações */
typedef enum Mes {Jan = 1, Fev, Mar, Abr, Mai, Jun, Jul, Ago, Set, Out,
          Nov, Dez
         };

int main()
{
    Mes m1, m2, m3; /*Agora o nome do tipo é Mes */

    m1 = Abr; /*Atribui valores */
    m2 = Jun; /*Atribui valores */

    m3 = m2 - m1; /*Operações aritméticas permitidas */
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
