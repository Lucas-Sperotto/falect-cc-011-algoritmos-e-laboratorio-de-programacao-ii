# Revisão técnica por conjunto de fontes

Complemento ao [registro de implementação](CODEX_IMPLEMENTATION_LOG.md). Os nomes abaixo são locais a cada pasta; o [catálogo](CATALOGO_FONTES.json) registra os IDs globais. As tabelas descrevem erros comprovados; os parágrafos de preservação e limites distinguem características didáticas e possíveis problemas.


## Aulas 1 e 2 — `src/Fontes_Aula_1/`

### Erros comprovados corrigidos

| Fonte(s) | Problema | Correção mínima |
|---|---|---|
| Prog1 | Cinco notas eram somadas sem leitura; soma int podia transbordar | Ler e validar as cinco entradas; converter antes da soma |
| Prog2/3/11 | scanf malsucedido deixava dados não inicializados usados | Verificar retorno e encerrar com código 1 antes do uso |
| Prog4/10 | Laço escrevia além do vetor de 50 notas | Conferir i < TAMANHO antes da escrita e excluir sentinela do total |
| Prog4/5/10 | Sentinela na primeira entrada dividia por zero | Informar ausência de notas e retornar 1 |
| Prog10 | printf %.2f recebia endereço da função media | Imprimir o valor m calculado |
| Prog6 | Mês inválido ultrapassava dmes; EOF usava dados indefinidos | Validar leitura, ano 1–9999, mês e dia após aplicar bissexto |
| Prog8/9 | Coordenadas sem limites indexavam fora de m[3][3] | Validar duas entradas e índices 0–2 antes do acesso |
| Prog12 | Totais acumulavam entre funcionários; zero provocava conversão indefinida de NaN para int | Reiniciar temp por funcionário; max zero produz barra vazia |
| Prog12 | Soma de três int podia transbordar | Usar long long nos totais e formato %lld |
| Prog13 | scanf %s podia exceder nome[80] | Usar %79s e conferir retorno |
| Prog14–21 | gets não limita texto, foi removida do C11 e falha com EOF | Preservar chamada histórica em comentário; usar ler_linha do cabeçalho comum |
| Prog15/17 | Deslocamento em nome curto lia bytes não inicializados | Guardar comprimento antes de imprimir substring |
| Prog18 | Percorria len+4 e podia ultrapassar array; endereço convertido a unsigned | Mostrar apenas string + terminador; size_t e %p com void* |
| Prog21 | EOF após resposta errada gerava repetição sem fim | Validar todas as leituras, inclusive no laço |
| Prog23 | strcpy com origem/destino sobrepostos tem comportamento indefinido | Preservar instrução histórica em comentário e usar memmove incluindo terminador; guardar pos |
| Prog24 | conio.h/getch indisponíveis em GCC Linux; data sem validação | Usar getchar em terminal com ENTER, checar calendário e EOF |
| Prog25 | conio.h/getche indisponíveis e gets permitia corromper arrays | Usar leitor de linha limitado e scanf para os sinais com retorno verificado |

### Características didáticas mantidas

- Prog4 e Prog5 ilustram a evolução para verificação de limites; o defeito histórico foi identificado em comentário, mantendo os nomes e os vetores.
- Prog7 continua a gerar 50 linhas com seis números de 1 a 60. Sorteios independentes podem repetir dezenas e a semente é a padrão: isso está comentado como exercício de matrizes/rand, sem implementar regras de uma aposta.
- Prog20 é explicitamente um contraexemplo nos slides 34–37 da Aula 2: resp != resposta compara endereços e o laço nunca terminava. A condição original permanece em comentário; a versão executável mostra uma única comparação de endereços e encaminha ao Prog21, que compara conteúdo com strcmp. Não foi transformado numa cópia de Prog21.
- Prog22 imprime resultados de strcmp, com comentário de que apenas o sinal é portátil.
- Prog25 mantém a mensagem histórica de 2008.
- strcat de Prog19 é seguro após limitar nome a 79 bytes: 13 bytes de saudação + 79 + terminador cabem nos 100 do destino. strcpy de Prog25 é entre regiões distintas e a mensagem limitada cabe no contorno; comentários registram essas premissas.

### Possíveis problemas e limites restantes

- Números digitados nos exemplos de scanf devem ser representáveis no tipo solicitado. A conferência do retorno evita usos após EOF/erro de formato, mas não transforma scanf num analisador completo de números fora da faixa. Conversão com strtol/strtof e validação de errno/faixa é alternativa futura se for exigida entrada numérica arbitrária.
- Exemplos com float mantêm arredondamento e intervalo do tipo, sem restringir notas ao intervalo 0–10, porque o enunciado não estabelece tal validação. O cenário INT_MAX do Prog1 verifica ausência de overflow na soma inteira; seu resultado em float arredonda para 2147483648.00.
- Comprimentos e deslocamentos de strings são em bytes, como nas aulas de C; não são índices de caracteres Unicode.
- Prog13 mantém leitura de uma palavra por scanf; entrada excedente fica no stdin, mas não é reutilizada pelo programa.
- Testes finitos não comprovam ausência de todos os defeitos. Nenhum teste estatístico de rand, teste exaustivo de calendários no executável C ou ensaio de falhas do sistema foi declarado.



Correção da revisão cruzada: Prog3/4/5/10 acumulam notas em `double`, preservando as entradas `float`, para evitar média infinita com valores finitos grandes.


## Aulas 5 a 8 — `src/Fontes_Aula_5_6_7_e_8/`

### Correções comprovadas

| Fontes | Alteração e motivo |
|---|---|
| Prog1, Prog5, Prog7, Prog12, Prog13, Prog14 | `%p` agora recebe `void *`; diferenças de ponteiros usam `%td`, sem truncamento de endereços. |
| Prog2, Prog3, Prog4, Prog11, Prog20, Prog21, Prog22, Prog29, Prog30, Prog34, Prog35 | Verificação do retorno de scanf antes de usar os dados. |
| Prog7 | Operações agora usam elementos do mesmo vetor de oito inteiros; elimina comparação/subtração entre objetos distintos e acessos fora do objeto. |
| Prog11 | Máximo de 50 notas e tratamento explícito de zero notas, sem divisão por zero. |
| Prog12, Prog13, Prog16, Prog19, Prog31 | `ler_linha` de `entrada_segura.h` substitui gets; rejeita linhas excessivas e EOF sem usar dados indefinidos. |
| Prog13 | Rotinas didáticas de strings renomeadas para não colidir com a biblioteca; apenas caracteres inicializados e terminador são mostrados. Cópia própria que aceita deslocamento à esquerda permanece identificada; não é strcpy padrão. |
| Prog15 | Leitura por linhas, validação de calendário (ano 1..9999, mês e dias reais, inclusive bissexto), interação confirmada com ENTER. Remove conio e impede índice inválido. |
| Prog16 | Limita a lista a 30 nomes. |
| Prog17 | Substitui getch por confirmação ENTER e remove execução de cls; desenho ASCII evita bytes OEM inválidos no terminal UTF-8. A rotação de ponteiros permanece. |
| Prog19 | Ponteiro de função passou a receber destino e capacidade, mantendo a finalidade didática de passar função como argumento. |
| Prog20, Prog21, Prog22 | Declaração `const int true=1`, válida em C11. |
| Prog25, Prog26 | Exibição dos dez elementos reais, comparador por relações sem overflow de subtração. |
| Prog26, Prog27 | Resultado da busca armazenado em int, preservando o sentinela -1. |
| Prog27 | Comparador acessa o tipo real dos elementos `char *` por `char *const *`; comentário sobre retorno de strcmp corrigido. |
| Prog28 | Comparador de população sem subtração; acesso const às estruturas. |
| Prog29, Prog30 | Alocações verificadas e memória liberada também nas falhas de leitura. Prog30 exige 1..100000 notas. |
| Prog31 | Leitura limitada, malloc verificado, conversões strtol/strtod com faixas e finitude; novo nó só entra na lista após preenchimento completo. Lista liberada em sucesso e falha. |
| Prog33 | Valida tecla 1..10 e capacidade de concatenação antes de copiar; preserva sequência ANSI histórica documentada, capturada apenas em arquivos nos testes. |
| Prog34 | Dimensão 1..100000, tipos coerentes no scanf, remoção de getche inexistente e limites antes da multiplicação. |
| Prog35 | Dimensões 1..1000 por eixo, produto limitado, tipos coerentes, remoção de getche e liberação das linhas anteriores em alocação parcial. |

### Características didáticas preservadas

- Prog3 continua passando valores: `troca(v1,v2)` não muda as variáveis da main; Prog4 mostra a troca por ponteiros. Não é um defeito a corrigir.
- Prog14 conserva `s1++` como linha comentada identificada como erro intencional; explica array versus ponteiro variável. A versão executável incrementa s2 e imprime `audações!`.
- Prog23 conserva as dereferências inválidas de void como comentários identificados e mostra conversões válidas, com referência ao Prog24.
- Prog34/35 continuam chamando print após destruir: o teste de NULL dentro da impressão demonstra a proteção e evita dereferência.
- Chamadas históricas system("PAUSE")/system("pause") permanecem comentadas.
- Busy wait e campainhas do Prog18 permanecem; o som depende do terminal e a pausa pode ser otimizada.
- A sequência ANSI.SYS do Prog33 é histórica e pode ser ignorada por terminais atuais; não executa o texto dos argumentos.

### Limitações e melhorias opcionais

- scanf permanece nas aulas onde é o mecanismo didático original; retorno, EOF e dimensões ordinárias são tratados. Tokens numéricos fora da faixa representável ainda são uma limitação do contrato da família scanf; isso não foi apresentado como cobertura de parsing arbitrário. Uma alternativa posterior pode usar strtol/strtof sistematicamente.
- Não foi injetada falha artificial de malloc para executar cada caminho de falta de memória; tais caminhos foram revisados e os testes usaram alocações pequenas.
- Limites de quantidade são guardas didáticas explícitas, não uma proposta de interface para dados ilimitados.
- Endereços de memória variam entre execuções; cenários verificam presença de endereço, sem valor fixo.
- Nenhum caminho foi renomeado nem PDF alterado.


Correção da revisão cruzada: Prog11/30 acumulam em `double` antes de retornar a média.


## Aulas 9 a 11 — `src/Fontes_Aula_9/` e `src/Fontes_Aula_10_e_11/`

### Correções comprovadas

- Aula 9: removida dependência conio; EOF distinguível de byte; mensagem identifica `unsigned int`; máscara unsigned por deslocamento; conversões hexadecimais com `strtoul`, rejeição de overflow/operando acima de16 bits; operações só aceitam deslocamentos0–15 e tokens limitados.
- Aulas10/11: abertura/leitura/gravação/fechamento checadas, EOF em `int`, contadores `size_t`, entrada limitada e conversões com faixa checada; sintaxe quebrada de `fopen` corrigida em Prog5. `TYPE` substituído por exibição pela biblioteca C.
- Escritores de Livro (Prog11/12/14): gets substituída por `ler_linha`; registro via `strtol` com faixa de short; preço via `strtod`, finito; retirados rewind(stdin)/conio. Estruturas inicializadas, gravação verificada e erros de entrada encerram com status1.
- Leitores de Livro: não interpretam registros parciais; terminadores de strings limitados; Prog15 usa `(rec-1)*sizeof(Livro)` (antes usava `nrec` e sempre lia o último), verifica ftell/fseek/fread e fecha em todos os caminhos.
- Prog16: referência histórica PRN documentada, saída Linux em stdout; laço condicionado ao sucesso de fgets evita duplicação/uso de buffer inválido.
- Prog17–20: cabeçalhos POSIX, ssize_t, EOF/erro/EINTR tratados, escritas parciais repetidas. Prog17 reserva terminador; Prog18 transfere contagem exata inclusive NUL sem off-by-one.
- Prog19: busca delimitada e contexto contido na janela; sobreposição mantém frases divididas entre blocos; tamanho explícito1–1024 bytes por frase e saída0 quando encontrado.
- Prog20: inode comparado antes de truncamento, impedindo destruir arquivo quando origem=destino, inclusive hard link; ambos descritores fechados.

### Preservação didática / possíveis problemas / opcionais

- Prog11/12 continuam exemplos duplicados com identidades SIGAA próprias; somente o cabeçalho histórico incorreto Prog11 em Prog12 foi acertado.
- `fwrite/fread` de structs continua formato nativo dependente de ABI, padding e endianness; está documentado no fonte. Não se pretende ler arquivos binários arbitrários ou transportar esses registros entre plataformas distintas. Serialização portátil permanece melhoria opcional.
- Exemplos POSIX permanecem identificados como POSIX/Linux; criar camada de compatibilidade Windows é opcional. No terminal canônico, getchar exige Enter (o antigo conio entregava caractere sem Enter).
- Contexto de busca mostra até100 bytes antes/depois disponíveis na janela; a frase inteira cabe e pode atravessar dois blocos. Frases maiores que1024 são rejeitadas com diagnóstico.
- Falhas reais de hardware, disco cheio e interrupções de sistema são tratadas nos caminhos de retorno, mas não foram injetadas/testadas. Execuções bem-sucedidas e sanitizers não constituem prova geral.



## Aulas 3 e 4 — `src/Fontes_Aula_3_e_4/`

| Fonte | Classificação e alteração |
|---|---|
| BitTest | Melhoria opcional: identifica a dependência da disposição dos campos de bits e marca a estrutura usada; não cria formato binário portátil. |
| Prog1/2 | Sem erro funcional identificado no cenário fixo; cabeçalho, LF e assinatura `main(void)`. |
| Prog3 | Erro comprovado: `printf %d` recebia `double`; substituído por `%.2f`. |
| Prog4 | Erro comprovado: valida leituras antes de usar valores, limita peças para impedir overflow; preços finitos entre 0 e 1 bilhão impedem overflow do total em float. |
| Prog5 | Erros comprovados: substitui conio/gets por linhas limitadas, trata EOF, capacidade de 50 vendas e só adiciona venda completa; peças 0..1000000, preços finitos 0..1000000000. Preserva matriz de structs e totais globais. |
| Prog6 | Codificação CP1252 corrigida; exibe a diferença calculada entre enumerações, eliminando variável sem uso. |
| Prog7 | Erro comprovado: typedef não declarava o alias Mes; corrigido. Conversão de codificação e uso da diferença como no Prog6. |
| Prog8 | Inicialização original 123.456 era convertida para o primeiro membro int; torna explícito 123 e imprime o membro inicializado. Característica didática: a união inicializa seu primeiro membro. |
| Prog9/11 | Erro comprovado: sizeof era impresso com %d; usar %zu. |
| Prog10 | Erro comprovado: distingue EOF antes da conversão a byte. Característica didática: acesso à representação por união/campos de bits permanece dependente do compilador; comentário sugere máscaras para alternativa portátil. |
| Prog12 | Erro comprovado: endereços recebiam %X; usar %p com void *. |
| Prog13 | União anônima C11 com discriminante preservada; literais cabem nos buffers; nenhum erro funcional identificado nos valores fixos. |

### Leitura comum e regressões posteriores

`src/entrada_segura.h` centraliza somente a substituição de gets: remove LF/CRLF, aceita linha de tamanho exato (inclusive sem LF no EOF), consome e rejeita linha excessiva, retorna erro em EOF antes da leitura. A revisão cruzada corrigiu CRLF no limite exato da capacidade; os testes unitários incluem essa fronteira. Comprimentos são em bytes, não caracteres Unicode.

Os exemplos numéricos que mantêm scanf/sscanf pressupõem tokens representáveis. Isso é possível problema documentado, não alegação de um parser para entradas arbitrárias. A revisão não altera o formato das structs, a progressão didática nem os PDFs.
