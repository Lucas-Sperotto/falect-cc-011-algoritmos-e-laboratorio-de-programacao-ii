/*
 * ID: A05-08-P07
 * Aula: ../../atividades/aulas-05-e-06.md
 * Objetivo: Mostra as operações possíveis com ponteiros.
 */
/* Prog7.c */
/* Mostra as operações possíveis com ponteiros */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    /* Aritmética e ordenação só são válidas dentro do mesmo array.
     * O original usava objetos x/y isolados e acessava memória fora deles. */
    unsigned int valores[8] = {5,6,7,8,9,10,11,12};
    unsigned int *px, *py;

    px = &valores[0];	/* Atribuições */
    py = &valores[1];

    if( px < py) /* Comparações */
        printf("py-px= %td\n", (py-px));/* Subtraçao */
    else
        printf("px-py= %td\n", (px-py));

    printf("px = %p", (void *)px);
    printf(", *px = %u", *px);	/* Op.Indireto */
    printf(", &px = %p\n", (void *)&px);	/* Op.Endereços */

    printf("py = %p", (void *)py);
    printf(", *py = %u", *py);
    printf(", &py = %p\n", (void *)&py);

    py++;	/* Incremento */

    printf("py = %p", (void *)py);
    printf(", *py = %u", *py);
    printf(", &py = %p\n", (void *)&py);

    px = py + 5; /* Somar inteiros */

    printf("px = %p", (void *)px);
    printf(", *px = %u", *px);
    printf(", &px = %p\n", (void *)&px);

    printf("px-py= %td\n", (px-py));

    // system("PAUSE");
    return 0;
}
