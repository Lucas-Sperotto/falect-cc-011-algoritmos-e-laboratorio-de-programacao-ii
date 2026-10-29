/* Prog20.c */
/* Copia um arquivo em outro, usando baixo nível */
#include <io.h> /* para read() e write() */
#include <stdlib.h> /* para exit() */
#include <string.h> /* para strlen(), memchr() */
#include <fcntl.h> /* necessario para flags */
#include <sys\stat.h> /* para permissao */

#define TAMBUFF 1024 /* tamanho do buffer */
char buff[TAMBUFF];

int main(int argc, char **argv)
{
    int fdOrigem, fdDest, BytesLidos;
    char *str="Formato: Fcopy ArqOrigem.xxx ArqDest.xxx\n";

    if(argc != 3)
    {
        write(1,str,strlen(str)); /* Imprime em stdout */
        exit(1) ;
    }
    if( (fdOrigem = open(argv[1], O_RDONLY | O_BINARY)) < 0)
    {
        str = "Arquivo não existe!";
        write(1,str,strlen(str)); /* Imprime em stdout */
        exit(1);
    }
    if((fdDest = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY |
                      O_BINARY , S_IWRITE))< 0)
    {
        str = "Nao posso abrir o arquivo de gravação.";
        write(1,str,strlen(str)); /* Imprime em stdout */
        exit(1);
    }
    while((BytesLidos = read(fdOrigem,buff,TAMBUFF)) > 0)
        write(fdDest,buff,BytesLidos);
    close(fdOrigem);
    close(fdDest);
    return 0;
}
