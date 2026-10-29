/*
 * ID: A03-04-P08
 * Aula: ../../atividades/aulas-03-e-04.md
 * Objetivo: Mostra o uso de uniões.
 */
/* Prog8.c */
/* Mostra o uso de uniões */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* Para strcpy() */

static union
{
    int idade;
    float salario;
} uInit = {123}; /* O primeiro membro é int: a fração original era truncada. */



int main(void)
{
    printf("Idade (primeiro membro da união): %d\n", uInit.idade);
    return 0;
}

