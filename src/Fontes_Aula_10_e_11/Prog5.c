/* Prog5.c */
/* Lê linha a linha do arquivo */
#include <stdio.h> /* define FILE */
#include <stdlib.h>

int main(void)
{
    FILE *fptr;  /* ponteiro para arquivo */
    char str[81];

    /*Abre p/leitura em modo texto*/
    if( (fptr = fopen(("TesteSTR.txt","r")) == NULL)
{
    puts("Não foi possível abrir o arquivo");
        exit(1);
    }

    while(fgets(str,80,fptr) != NULL) /*Lê uma linha de texto */
    printf("%s",str);

    fclose(fptr);
    // system("pause");
    return 0;
}
