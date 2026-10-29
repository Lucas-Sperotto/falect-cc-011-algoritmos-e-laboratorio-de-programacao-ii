/* Prog19.c */
/* Procura frase no arquivo usando baixo nível */
#include <io.h> /* para read() e write() */
#include <stdlib.h> /* para exit() */
#include <string.h> /* para strlen(), memchr() */
#include <fcntl.h> /* necessario para flags */
#include <stdio.h> /* para NULL etc. ..*/

#define TAMBUFF 1024 /* tamanho do buffer */
char buff[TAMBUFF];

/* procura() */
/* procura frase no buffer */
void procura(char *frase, int tambuf)
{
    char *ptr,*p;
    ptr = buff;
    while((ptr = memchr(ptr,frase[0],tambuf)) != NULL)
        if(memcmp(ptr,frase,strlen(frase)) == 0)
        {
            puts("Primeira ocorrencia da frase: ");
            for(p = ptr- 100; p < ptr+100; p++)
                putchar(*p);
            exit(1);
        }
        else
            ptr++;
}

int main(int argc, char **argv)
{
    char *str="Formato: Procura NomeArq.xxx frase\n";
    int fd, BytesLidos;

    if(argc != 3)
    {
        write(1,str,strlen(str)); /* Imprime em stdout */
        exit(1) ;
    }

    if( (fd = open(argv[1], O_RDONLY )) < 0)
    {
        str = "Arquivo não existe!";
        write(1,str,strlen(str)); /* Imprime em stdout */
        exit(1);
    }

    while((BytesLidos = read(fd,buff,TAMBUFF)) > 0)
        procura(argv[2],BytesLidos);
    close(fd);
    str = "Frase nao encontrada\n";
    write(1,str,strlen(str)); /* Imprime em stdout */
    return 0;
}
