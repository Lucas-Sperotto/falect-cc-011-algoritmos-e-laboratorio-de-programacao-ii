/*
 * ID: A10-11-P20
 * Aula: ../../aulas/aula-11/README.md
 * Objetivo: Copia o conteúdo de um arquivo para outro utilizando operações de baixo nível.
 */
/* Prog20.c — cópia binária com read/write e descritores POSIX. */
#define _POSIX_C_SOURCE 200809L
#include <unistd.h> /* POSIX: read, write, close; substitui io.h. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>
#include <sys/stat.h>
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
    struct stat origem, destino;
    int status = 0;
    if (argc != 3) { fprintf(stderr, "Uso: %s origem destino\n", argv[0]); return 1; }
    int fdOrigem = open(argv[1], O_RDONLY);
    if (fdOrigem < 0) { perror(argv[1]); return 1; }
    /* Ainda não truncar: os dois nomes podem referir-se ao mesmo inode. */
    int fdDest = open(argv[2], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fdDest < 0) { perror(argv[2]); close(fdOrigem); return 1; }
    if (fstat(fdOrigem, &origem) < 0 || fstat(fdDest, &destino) < 0 ||
        (origem.st_dev == destino.st_dev && origem.st_ino == destino.st_ino)) {
        fputs("Origem e destino devem ser arquivos distintos e acessíveis.\n", stderr);
        status = 1;
    } else if (ftruncate(fdDest, 0) < 0) {
        perror("ftruncate"); status = 1;
    }
    while (!status) {
        ssize_t BytesLidos = read(fdOrigem, buff, sizeof buff);
        if (BytesLidos < 0 && errno == EINTR) continue;
        if (BytesLidos < 0) { perror("read"); status = 1; break; }
        if (BytesLidos == 0) break;
        if (!escreve_tudo(fdDest, buff, (size_t)BytesLidos)) { status = 1; break; }
    }
    if (close(fdOrigem) < 0) status = 1;
    if (close(fdDest) < 0) status = 1;
    return status;
}
