/*
 * ID: A10-11-P18
 * Aula: ../../atividades/aula-11.md
 * Objetivo: Lê e imprime o conteúdo de um arquivo utilizando operações de baixo nível.
 */
/* Prog18.c — lê e imprime todos os bytes usando operações POSIX. */
#include <unistd.h> /* POSIX: read, write, close; substitui io.h. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define TAMBUFF 1024

/* write() pode transferir menos bytes que o solicitado, ou ser interrompida. */
static int escreve_tudo(int fd, const void *dados, size_t tamanho)
{
    const unsigned char *p = dados;
    while (tamanho > 0) {
        ssize_t enviados = write(fd, p, tamanho);
        if (enviados < 0 && errno == EINTR) continue;
        if (enviados <= 0) return 0;
        p += (size_t)enviados;
        tamanho -= (size_t)enviados;
    }
    return 1;
}

int main(int argc, char **argv)
{
    char buff[TAMBUFF];
    ssize_t BytesLidos;
    int status = 0;
    if (argc != 2) { fprintf(stderr, "Uso: %s nomearq\n", argv[0]); return 1; }
    /* POSIX não distingue modo texto/binário; O_BINARY não existe no Linux. */
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) { perror(argv[1]); return 1; }
    for (;;) {
        BytesLidos = read(fd, buff, sizeof buff);
        if (BytesLidos < 0 && errno == EINTR) continue;
        if (BytesLidos < 0) { perror("read"); status = 1; break; }
        if (BytesLidos == 0) break;
        /* Não há string: NUL faz parte dos dados, e não se acrescenta '\0'. */
        if (!escreve_tudo(STDOUT_FILENO, buff, (size_t)BytesLidos)) {
            status = 1; break;
        }
    }
    if (close(fd) < 0) status = 1;
    return status;
}
