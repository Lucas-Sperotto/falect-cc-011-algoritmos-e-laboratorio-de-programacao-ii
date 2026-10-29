/* Prog14.c */
/* Mostra o uso de ponteiro para cadeias de caracteres */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char s1[] = "Saudações!";
    char *s2 = "Saudações!";

    printf("%p\n", s1);
    printf("%p\n", s2);

    s1++; /* ERRO. Não podemos incrementar uma constante */
    s2++; /* OK */

    printf("%s\n", s2); /* Imprime: Saudações */
    return 0;
}
