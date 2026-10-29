/* Prog1.c */
/* Mostra o uso do operador de complemento ~ */
/* codifica os bytes digitados */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    unsigned char ch;
    while((ch=getch())!= 'X')
        printf("%c", ~ch);
    system("pause");
    return 0;
}


