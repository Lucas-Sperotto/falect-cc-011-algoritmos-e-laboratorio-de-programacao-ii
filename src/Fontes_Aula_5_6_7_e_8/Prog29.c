/* Prog29.c */
/* mostra o uso de malloc() */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *pi;

    pi = (int *) malloc(sizeof(int));

    puts("Digite um número: ");
    scanf("%d", pi);
    printf("\nVocê digitou o número %d\n", *pi);

    free(pi);

    system("PAUSE");
    return 0;
}
