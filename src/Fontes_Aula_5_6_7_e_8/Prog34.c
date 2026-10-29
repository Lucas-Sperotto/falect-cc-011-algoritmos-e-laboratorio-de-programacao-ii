/* Prog34.c */
/* Alocação de Vetores */
#include <stdio.h>
#include <stdlib.h>

int *aloca_array(int);               /* Função para reservar a mémória do array                     */
void init_array(int *, int);         /* Função para preencher o array com valores aleatórios        */
void print_array(int *, int);        /* Função para printar o array na tela                         */
void destruir_array(int **, int);    /* Função para liberar o espaço alocado com a função free()    */


int main()
{
    unsigned int size;
    int *Vet; /*Cria o ponteiro para o array */

    printf("Informe o número de elementos do array: ");
    scanf("%d", &size);

    Vet = (int *)aloca_array(size);

    init_array(Vet, size);
    print_array(Vet, size);

    destruir_array(&Vet, size);

    print_array(Vet, size);

    return 0;
}

/* função reserva a memória usando a função malloc e */
/* testa se o ponteiro foi corretamente alocado      */
int *aloca_array(int Size)
{
    int *Array = (int *)malloc(Size*sizeof(int));

    if(Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Alocar\n");
        getche();
        exit(1);
    }
    return ((int *)Array);
}

void init_array(int *Array, int Size)
{
    unsigned register int i = 0;
    for(i = 0; i < Size; i++)
    {
        Array[i] = rand() % Size;
    }
}

/* função testa se o ponteiro existe antes de imprimir */
void print_array(int *Array, int Size)
{
    unsigned register int i = 0;

    if(Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Imprimir: Ponteiro NULL\n");
        return;
    }

    for(i = 0; i < Size; i++)
    {
        printf("%d \t", Array[i]);
        printf("\n");
    }
    printf("\n");
}
/* função testa se o ponteiro existe antes de destruir */
/* destroi ponteiro chamando a função free() e depois  */
/* coloca o ponteiro como NULL para evitar que seja    */
/* usado em outras partes do código                    */
void destruir_array(int **Array, int Size)
{
    if(Array == NULL)
    {
        printf("\tERRO!\n\n**Não foi Possivel Destruir: Ponteiro NULL\n");
        return;
    }

    free(*Array);
    *Array = NULL;
}
