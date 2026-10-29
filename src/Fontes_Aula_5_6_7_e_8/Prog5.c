/*
 * ID: A05-08-P05
 * Aula: ../../atividades/aulas-05-e-06.md
 * Objetivo: Mostra o uso de ponteiros declarados dentro da função main().
 */
/* Prog5.c */
/* Mostra o uso de ponteiros declarados
   dentro da função main() */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int x=4, y=7;
    int *px,*py;

    printf("&x = %p\t  x = %d\n", (void *)&x , x);
    printf("&y = %p\t  y = %d\n", (void *)&y , y);

    px = &x;
    py = &y;

    printf("px = %p\t*px = %d\n", (void *)px,*px);
    printf("py = %p\t*py = %d\n", (void *)py,*py);

    // system("PAUSE");
    return 0;
}
