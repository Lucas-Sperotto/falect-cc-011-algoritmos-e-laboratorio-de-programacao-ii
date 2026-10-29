/* Prog16.c */
/* Imprime esse arquivo na impressora */
#include <stdio.h> /* define FILE */
#include <stdlib.h>

int main()
{

    char buff[80];
    FILE *fptr, *fprn; /* ponteiro para arquivo */

    if((fptr = fopen("FilePrint.C","r"))==NULL)
    {
        puts("Arquivo FilePrint.C não foi encontrado");
        exit(1);
    }

    if((fprn = fopen("PRN","w"))==NULL) /* Abre arquivo impressora */
    {
        puts("Impressora indisponivel.");
        exit(1);
    }

    while(!feof(fptr))
    {
        fgets(buff,80,fptr); /*Lê uma linha de texto */
        fputs(buff,fprn);    /*Imprime na impressora */
    }
    fclose(fptr);
    fclose(fprn);
    system("pause");
    return 0;
}
