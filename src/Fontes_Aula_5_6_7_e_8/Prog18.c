/*
 * ID: A05-08-P18
 * Aula: ../../atividades/aulas-06-e-07.md
 * Objetivo: Mostra o uso de ponteiros para funções.
 */
/* Prog18.c */
/* Mostra o uso de ponteiro para função */
#include <stdio.h>
#include <stdlib.h>

void doisbeep(void); /* protótipo */

int main(void)
{
    void (*pf)(void);/* ponteiro p/fção void que recebe void */

    pf = doisbeep; /* nome da função sem os parênteses */

    (*pf)();/* chama a função */

    // system("PAUSE");
    return 0;
}

/* doisbeep() */
/* toca o alto-falante duas vezes */
void doisbeep(void)
{
    unsigned i;
    printf("\a");
    for(i=0; i < 800000 ; i++); /* dar um tempo */
    printf("\a");
}
