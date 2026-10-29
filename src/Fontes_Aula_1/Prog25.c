/* Prog25.c */
/* Imprime um cartão de natal */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>	/* para getche() */

int main()
{
    char Nome[81], Mensagem[39], sEsquerdo, sDireito, Contorno[42];
    int Tamanho, Lado1=0, me=20, Direito, ns, i, fim, Lado, j;

    printf("\nDestinatario: ");
    gets(Nome);
    printf("\nMensagem dentro da arvore: ");
    gets(Mensagem);
    Tamanho=strlen(Mensagem);
    printf("\nSinal interno direito:");
    sDireito=getche();
    printf("\nSinal interno esquerdo:");
    sEsquerdo=getche();
    Direito=38-Tamanho;
    Contorno[0]='/';
    ns=Direito/2;
    for(i=1; i<=ns ; i++) Contorno[i]=sEsquerdo;
    strcpy(&Contorno[i], Mensagem);
    fim=strlen(Contorno);
    for(i=fim; i < fim+ns ; i++) Contorno[i]=sDireito;
    Contorno[i]='\\';
    Contorno[i+1]='\0';
    fim=strlen(Contorno);

    /* Impressão da árvore */
    printf("\n");
    for(i=0; i < (80-strlen(Nome))/2; i++) printf(" ");
    printf("%s\n\n\n",Nome);
    for(i=1; i<=36; i++)
    {
        Lado=i-Lado1;
        for(j=1; j <= me+20-Lado; j++) printf(" ");
        for(j=0; j<Lado ; j++) printf("%c",Contorno[j]);
        printf("%s\n",&Contorno[fim-Lado]);
        if(!(i%4)) Lado1=Lado1+2;
    }
    for(i=0; i<me-1; i++) printf(" ");
    printf("%c",'/');
    for(i=0; i<20; i++) printf("%c",sEsquerdo);
    for(i=0; i<20; i++) printf("%c",sDireito);
    printf("%c\n",'\\');
    for(i=0; i<4; i++)
    {
        for(j=0; j<me+18; j++) printf(" ");
        printf("| |\n");
    }
    printf("\n\n");
    for(i=0; i<me+15; i++) printf(" ");
    printf("FELIZ NATAL\n");
    for(i=0; i<me+11; i++) printf(" ");
    printf("E UM PROSPERO 2008!\n");
    system("PAUSE");
    return 0;
}
