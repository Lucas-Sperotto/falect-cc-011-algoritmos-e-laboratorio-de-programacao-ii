/* Prog33.c */
/* Atribui o texto digitado na linha de comando a uma tecla de função */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int tecla, j;
    char str[80];

    if(argc < 3)
    {
        printf("Exemplo de uso: C:\\>Teclaf 2 dir *.c");
        exit(1) ;
    }
    tecla = atoi(argv[1]);
    strcpy(str,argv[2]);
    for(j=3; j< argc; j++)
    {
        strcat(str," ");
        strcat(str,argv[j]);
    }
    if( strcmp(str, "null" )==0) /* limpa tecla */
        strcpy(str,"");
    printf("\x1B[0;%d;\"%s\";13p",tecla+58,str);
    system("PAUSE");
    return 0;
}
