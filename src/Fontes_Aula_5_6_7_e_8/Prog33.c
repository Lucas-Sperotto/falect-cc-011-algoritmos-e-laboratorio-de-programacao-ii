/*
 * ID: A05-08-P33
 * Aula: ../../aulas/aula-08/README.md
 * Objetivo: Mostra a utilização de argumentos da linha de comando para configurar teclas de função.
 */
/* Prog33.c */
/* Atribui o texto digitado na linha de comando a uma tecla de função */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int tecla, j;
    char *fim;
    long valor;
    size_t usado;
    char str[80];

    if(argc < 3)
    {
        printf("Exemplo de uso: ./programa 2 texto");
        exit(1) ;
    }
    valor = strtol(argv[1], &fim, 10);
    if (*argv[1] == '\0' || *fim != '\0' || valor < 1 || valor > 10)
        return 1;
    tecla = (int)valor;
    str[0] = '\0';
    usado = 0;
    for (j=2; j<argc; j++)
    {
        size_t tamanho = strlen(argv[j]);
        size_t separador = j > 2 ? 1u : 0u;
        if (separador > sizeof str - 1 - usado ||
            tamanho > sizeof str - 1 - usado - separador) return 1;
        if (separador) str[usado++] = ' ';
        memcpy(str+usado, argv[j], tamanho+1);
        usado += tamanho;
    }
    /* Sequência histórica de redefinição de teclas ANSI.SYS (DOS).
     * Terminais atuais podem ignorá-la; não executa o texto informado. */
    if( strcmp(str, "null" )==0) /* limpa tecla */
        strcpy(str,"");
    printf("\x1B[0;%d;\"%s\";13p",tecla+58,str);
    // system("PAUSE");
    return 0;
}
