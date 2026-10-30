/*
 * ID: A10-11-P10
 * Aula: ../../aulas/aula-10/README.md
 * Objetivo: Copia arquivos utilizando as funções fread() e fwrite().
 */
/* Prog10.c — copia com fread/fwrite e exibe os bytes sem comandos Windows. */
#include <stdio.h>
#include <stdlib.h>

int CopiaArquivo(const char *Origem, const char *Destino);

int main(void)
{
    const char Origem[] = "CopiaArq.C", Destino[] = "CopiaArq.cpy";
    if (!CopiaArquivo(Origem, Destino)) return 1;
    FILE *copia = fopen(Destino, "rb");
    int ch, status = 0;
    if (copia == NULL) { perror(Destino); return 1; }
    while ((ch = fgetc(copia)) != EOF) {
        if (putchar(ch) == EOF) { status = 1; break; }
    }
    if (ferror(copia)) status = 1;
    if (fclose(copia) == EOF) status = 1;
    // system("pause");
    return status;
}

int CopiaArquivo(const char *Origem, const char *Destino)
{
    unsigned char buffer[1024];
    size_t BytesLidos;
    int sucesso = 1;
    FILE *fOrigem = fopen(Origem, "rb"), *fDest;
    if (fOrigem == NULL) { perror(Origem); return 0; }
    fDest = fopen(Destino, "wb");
    if (fDest == NULL) { perror(Destino); fclose(fOrigem); return 0; }
    while ((BytesLidos = fread(buffer, 1, sizeof buffer, fOrigem)) > 0) {
        if (fwrite(buffer, 1, BytesLidos, fDest) != BytesLidos) {
            sucesso = 0; break;
        }
    }
    if (ferror(fOrigem)) sucesso = 0;
    if (fclose(fOrigem) == EOF) sucesso = 0;
    if (fclose(fDest) == EOF) sucesso = 0;
    return sucesso;
}
