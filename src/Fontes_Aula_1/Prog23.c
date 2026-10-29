/* Prog23.c */
/* Mostra o uso de strcpy() */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strdel(char[], int); /*Protótipo */

int main()
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
    strcpy(str+pos, str+pos+1);
}
