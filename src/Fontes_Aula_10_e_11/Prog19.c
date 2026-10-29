/*
 * ID: A10-11-P19
 * Aula: ../../atividades/aula-11.md
 * Objetivo: Procura uma sequência de caracteres em um arquivo utilizando operações de baixo nível.
 */
/* Prog19.c — busca frase com janela de bytes e contexto limitado. */
#include <unistd.h> /* POSIX: read, write, close; substitui io.h. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#define TAMBUFF 1024
/* Frases de até TAMBUFF bytes; a janela retém frase parcial e contexto. */
static char buff[3 * TAMBUFF];

static int procura(const char *frase, size_t tambuf)
{
    size_t tamanho = strlen(frase), pos = 0;
    while (pos + tamanho <= tambuf) {
        /* Só procurar posições em que a frase inteira ainda cabe. */
        char *ptr = memchr(buff + pos, (unsigned char)frase[0], tambuf - pos - tamanho + 1);
        if (ptr == NULL) return 0;
        size_t inicio = (size_t)(ptr - buff);
        if (memcmp(ptr, frase, tamanho) == 0) {
            size_t de = inicio > 100 ? inicio - 100 : 0;
            size_t ate = inicio + tamanho + 100;
            if (ate > tambuf) ate = tambuf;
            puts("Primeira ocorrência da frase: ");
            if (fwrite(buff + de, 1, ate - de, stdout) != ate - de || putchar('\n') == EOF)
                return -1;
            return 1;
        }
        pos = inicio + 1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    size_t usados = 0, tamanho;
    int status = 0, encontrada = 0;
    if (argc != 3) { fprintf(stderr, "Uso: %s nomearq frase\n", argv[0]); return 1; }
    tamanho = strlen(argv[2]);
    if (tamanho == 0 || tamanho > TAMBUFF) {
        fputs("A frase deve ter entre 1 e 1024 bytes.\n", stderr); return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) { perror(argv[1]); return 1; }
    for (;;) {
        ssize_t lidos = read(fd, buff + usados, TAMBUFF);
        if (lidos < 0 && errno == EINTR) continue;
        if (lidos < 0) { perror("read"); status = 1; break; }
        if (lidos == 0) break;
        usados += (size_t)lidos;
        int resultado = procura(argv[2], usados);
        if (resultado != 0) { encontrada = resultado > 0; status = resultado < 0; break; }
        /* Preserva uma possível frase dividida entre duas chamadas a read(),
         * mais 100 bytes de contexto anterior; nunca indexa fora da janela. */
        size_t manter = tamanho - 1 + 100;
        if (manter > usados) manter = usados;
        memmove(buff, buff + usados - manter, manter);
        usados = manter;
    }
    if (close(fd) < 0) status = 1;
    if (!status && !encontrada) puts("Frase não encontrada");
    return status;
}
