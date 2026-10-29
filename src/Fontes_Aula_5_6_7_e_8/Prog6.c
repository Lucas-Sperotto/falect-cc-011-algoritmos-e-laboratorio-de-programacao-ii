/* Prog6.c */
/* Mostra a inicialização do ponteiro */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x,y;
    int *px = &x;	/* Inicializa px com o endereço de x */

    *px = 14;	/* O mesmo que x = 14 */
    y = *px;	/* O mesmo que y = x  */

    printf("y = %d\n", y);

    system("PAUSE");
    return 0;
}

