/* Prog10.c */
/* Mostra o uso de fread() e fwrite() */
#include <stdio.h> /* define FILE */
#include <stdlib.h>

void CopiaArquivo(const char* Origem, const char *Destino);

int main()
{
    char Origem[] = "CopiaArq.C";
    char Destino[]= "CopiaArq.cpy";

    CopiaArquivo(Origem, Destino);
    system("type CopiaArq.cpy");
    system("pause");
    return 0;
}

void CopiaArquivo(const char* Origem, const char *Destino)
{
    unsigned char buffer[1024];
    int BytesLidos;

    FILE *fOrigem, *fDest; /* ponteiro para arquivo */

    if((fOrigem = fopen(Origem,"rb"))==NULL) return;
    if((fDest = fopen(Destino,"wb"))== NULL) return;
    do
    {
        BytesLidos= fread(buffer,sizeof(char),sizeof(buffer), fOrigem);
        fwrite(buffer,sizeof(char), BytesLidos, fDest);
    }
    while(BytesLidos);

    fclose(fOrigem);
    fclose(fDest);
}
