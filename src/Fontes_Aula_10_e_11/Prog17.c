/* Prog17.c */
/* Lê de stdin e imprime em stdout usando baixo nível */
#include <io.h> /* para read() e write() */
#include <stdlib.h> /* para system() */
#include <string.h> /* para strlen() */

int main()
{
    char *str="Digite o nome seu nome: ";
    char nome[80];
    int BytesLidos;

    write(1,str,strlen(str)); /* Imprime em stdout */

    BytesLidos=read(0,nome,80); /* Lê de stdin */

    nome[BytesLidos + 1]='\0';

    str="Seu nome é ";
    write(1,str,strlen(str)); /* Imprime em stdout */
    write(1,nome,strlen(nome));
    // system("pause");
    return 0;
}
