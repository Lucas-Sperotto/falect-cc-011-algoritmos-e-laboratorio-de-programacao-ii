/* Prog9.c */
/* Imprime os elementos de uma matriz usando notação ponteiro */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    static int M[5]= {92,81,70,69,58};
    int i;
    for(i=0; i<5; i++)
        printf("%d\n", *(M + i)); /* Notação ponteiro */

    system("PAUSE");
    return 0;
}
