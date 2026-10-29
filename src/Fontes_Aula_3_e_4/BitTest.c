
typedef struct
{
    unsigned short CodAscii: 8; /* Bits 0 a 7 */
    unsigned short CorFrente: 3; /* Bits 8 a 10 */
    unsigned short Intenso: 1; /* Bits 11 */
    unsigned short CorFundo: 3; /* Bits 12 a 14 */
    unsigned short Piscante: 1; /* Bits 15 */
} Int16Bits;

int main()
{
    Int16Bits A;
    A.CodAscii = 'A';
    A.CorFrente = 3;    /* Branco para a cor de frente */
    A.Intenso = 1;      /* Intensificada a cor de frente */
    A.CorFundo = 0;     /* Preto para a cor de fundo */
    A.Piscante = 1;     /* Escolhe atributos piscante */
}




