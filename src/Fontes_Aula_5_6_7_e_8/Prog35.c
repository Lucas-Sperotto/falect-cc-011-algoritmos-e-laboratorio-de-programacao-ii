/* Prog35.c */
/* Alocação de Matrizes */
#include <stdio.h>
#include <stdlib.h>

int **aloca_array(int, int);               /* Função para reservar a mémória do array                     */
void init_array(int **, int, int);         /* Função para preencher o array com valores aleatórios        */
void print_array(int **, int, int);        /* Função para printar o array na tela                         */
void destruir_array(int ***, int, int);    /* Função para liberar o espaço alocado com a função free()    */


int main()
{
    unsigned int Lin, Col;
    int **Mat; /*Cria o ponteiro para o array */

    printf("\nInforme o número de linhas do array: ");
    scanf("%d", &Lin);
    printf("\nInforme o número de colunas do array: ");
    scanf("%d", &Col);

    Mat = (int **)aloca_array(Lin, Col);

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
    unsigned register int i;
    int **Array = (int **)malloc(lin * sizeof(int*));

    if(Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Alocar\n");
        getche();
        exit(1);
    }
    for(i = 0; i < lin; i++)
    {
        Array[i] = (int *)malloc(col * sizeof(int));
        if(Array[i] == NULL)
        {
            printf("\tERRO!\n\n**Não foi Possivel Alocar\n");
            getche();
            exit(1);
        }
    }
    return ((int **)Array);
}

void init_array(int **Array, int lin, int col)
{
    unsigned register int i = 0, j = 0;

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
    unsigned register int i = 0, j = 0;

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
    unsigned register int i = 0;

    if(Array == NULL)
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
