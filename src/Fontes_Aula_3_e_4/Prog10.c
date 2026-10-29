/*
 * ID: A03-04-P10
 * Aula: ../../atividades/aulas-03-e-04.md
 * Objetivo: Mostra união com estrutura.
 */
/* Prog10.c */
/* Mostra união com estrutura */
/* Imprime um caractere em binário */
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    /* cada membro com um bit de tamanho */
    unsigned char bit0: 1; /* bit 0 */
    unsigned char bit1: 1; /* bit 1 */
    unsigned char bit2: 1; /* bit 2 */
    unsigned char bit3: 1; /* bit 3 */
    unsigned char bit4: 1; /* bit 4 */
    unsigned char bit5: 1; /* bit 5 */
    unsigned char bit6: 1; /* bit 6 */
    unsigned char bit7: 1; /* bit 7 */
} Bits;

typedef union
{
    unsigned char ch;
    Bits x;
} Binario;

int main(void)
{
    Binario B;
    printf("Digite um caractere: ");
    int entrada = getchar();
    if (entrada == EOF)
        return EXIT_FAILURE;
    B.ch = (unsigned char)entrada;
    /* A sobreposição de união e ordem dos bitfields dependem do compilador.
     * Para uma representação portátil, use máscaras e deslocamentos de B.ch. */
    printf("O caractere digitado é: %c\n", B.ch);
    printf("O valor em binário correspondente é: ");

    printf("%d", B.x.bit7);
    printf("%d", B.x.bit6);
    printf("%d", B.x.bit5);
    printf("%d", B.x.bit4);
    printf("%d", B.x.bit3);
    printf("%d", B.x.bit2);
    printf("%d", B.x.bit1);
    printf("%d", B.x.bit0);
    printf("\n");

    // system("pause");
    return 0;
}

