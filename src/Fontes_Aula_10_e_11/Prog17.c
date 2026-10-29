/*
 * ID: A10-11-P17
 * Aula: ../../atividades/aula-11.md
 * Objetivo: Mostra operações de entrada e saída de baixo nível utilizando stdin e stdout.
 */
/* Prog17.c — stdin/stdout com operações POSIX de baixo nível. */
#include <unistd.h> /* POSIX: read, write, close; substitui io.h. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

int main(void)
{
    const char *str = "Digite o seu nome: ";
    char nome[80];
    ssize_t BytesLidos;
    if (!escreve_tudo(STDOUT_FILENO, str, strlen(str))) return 1;
    do {
        BytesLidos = read(STDIN_FILENO, nome, sizeof nome - 1);
    } while (BytesLidos < 0 && errno == EINTR);
    if (BytesLidos < 0) { perror("read"); return 1; }
    /* Reserva o terminador; read() retorna -1 em erro e 0 em EOF. */
    nome[BytesLidos] = '\0';
    str = "Seu nome é ";
    if (!escreve_tudo(STDOUT_FILENO, str, strlen(str)) ||
        !escreve_tudo(STDOUT_FILENO, nome, (size_t)BytesLidos)) return 1;
    // system("pause");
    return 0;
}
