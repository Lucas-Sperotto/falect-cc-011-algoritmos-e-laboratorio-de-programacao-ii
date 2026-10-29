/*
 * ID: A05-08-P35
 * Aula: ../../atividades/aula-08.md
 * Objetivo: Mostra alocação, inicialização e liberação dinâmica de matrizes.
 */
/* Prog35.c */
/* Alocação de Matrizes */
#include <stdio.h>
#include <stdlib.h>

int **aloca_array(int, int);               /* Função para reservar a memória do array                     */
void init_array(int **, int, int);         /* Função para preencher o array com valores aleatórios        */
void print_array(int **, int, int);        /* Função para printar o array na tela                         */
void destruir_array(int ***, int, int);    /* Função para liberar o espaço alocado com a função free()    */


int main(void)
{
    int Lin, Col;
    int **Mat; /*Cria o ponteiro para o array */

    printf("\nInforme o número de linhas do array: ");
    if (scanf("%d", &Lin) != 1 || Lin <= 0 || Lin > 1000) return 1;
    printf("\nInforme o número de colunas do array: ");
    if (scanf("%d", &Col) != 1 || Col <= 0 || Col > 1000) return 1;

    Mat = aloca_array(Lin, Col);
    if (Mat == NULL) return 1;

    init_array(Mat, Lin, Col);

    print_array(Mat, Lin, Col);

    destruir_array(&Mat, Lin, Col);

    print_array(Mat, Lin, Col);

    return 0;
}

/* função reserva a memória usando a função malloc e */
/* testa se o ponteiro foi corretamente alocado      */
/* deve-se reservar um vetor de ponteiros para alocar as linhas */
/* para cada linha se aloca um vetor com os elementos das colunas */
int **aloca_array(int lin, int col)
{
    int i;
    int **Array;
    if (lin <= 0 || col <= 0 || lin > 1000 || col > 1000) return NULL;
    Array = malloc((size_t)lin * sizeof *Array);

    if(Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Alocar\n");
        exit(1);
    }
    for(i = 0; i < lin; i++)
    {
        Array[i] = malloc((size_t)col * sizeof *Array[i]);
        if(Array[i] == NULL)
        {
            printf("\tERRO!\n\n**Não foi Possivel Alocar\n");
                /* Libera as linhas anteriores se a alocação for parcial. */
            while (i > 0) free(Array[--i]);
            free(Array);
            exit(1);
        }
    }
    return ((int **)Array);
}

void init_array(int **Array, int lin, int col)
{
    int i = 0, j = 0;

    for(i = 0; i < lin; i++)
    {
        for(j = 0; j < col; j++)
        {
            Array[i][j] = rand() % (lin * col);
        }
    }
}

/* função testa se o ponteiro existe antes de imprimir */
void print_array(int **Array, int lin, int col)
{
    int i = 0, j = 0;

    if(Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Imprimir: Ponteiro NULL\n");
        return;
    }

    for(i = 0; i < lin; i++)
    {
        for(j = 0; j < col; j++)
        {
            printf("%d \t", Array[i][j]);
        }
        printf("\n");
    }
}

/* função testa se o ponteiro existe antes de destruir */
/* destroi ponteiro chamando a função free() e depois  */
/* coloca o ponteiro como NULL para evitar que seja    */
/* usado em outras partes do código                    */
void destruir_array(int ***Array, int lin, int col)
{
    int i = 0;

    (void)col; /* O número de colunas não é necessário para free. */
    if(Array == NULL || *Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Destruir: Ponteiro NULL\n");
        return;
    }

    for(i = 0; i < lin; i++)
    {
        free((*Array)[i]);
    }
    free(*Array);
    *Array = NULL;
}
