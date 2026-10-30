/*
 * ID: A01-P13
 * Aula: ../../aulas/aula-02/README.md
 * Objetivo: Mostra o uso de strings.
 */
/* Prog13.c */
/* Mostra o uso de strings */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char nome[80];
    printf("Digite o seu nome: ");
    /* O limite reserva um byte para o terminador da string. */
    if (scanf("%79s", nome) != 1) {
        fputs("Nome não informado.\n", stderr);
        return 1;
    }
    printf("Saudações %s.\n", nome);
    // system("PAUSE");
    return 0;
}
