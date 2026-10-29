/* Prog18.c */
/* Mostra o uso de ponteiro para função */
#include <stdio.h>
#include <stdlib.h>

void doisbeep(void); /* protótipo */

int main()
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
