/*
 * ID: A01-P23
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Mostra o uso de strcpy().
 */
/* Prog23.c */
/* Remove caractere: memmove() permite as áreas sobrepostas do exemplo. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strdel(char[], int); /*Protótipo */

int main(void)
{
    char str[] = "Carrta";

    printf("%s\n", str);
    strdel(str,2);
    printf("%s\n", str);

    // system("PAUSE");
    return 0;
}

/* Apaga um caractere de uma cadeia */
void strdel(char str[], int pos)
{
    size_t tamanho = strlen(str);
    if (pos < 0 || (size_t)pos >= tamanho)
        return;
    /* Histórico: strcpy(str+pos, str+pos+1) sobrepunha origem e destino. */
    memmove(str+pos, str+pos+1, tamanho-(size_t)pos);
}
