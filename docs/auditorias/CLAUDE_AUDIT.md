# Documentação das aulas — registro do trabalho

**Responsável:** Claude Code (modelo Claude Opus 5.5), a pedido do docente. **Data:** 30/10/2026. **Ramo:** `claude/transcricao-aulas`, criado a partir de `codex/auditoria-fontes-c` (revisão dos fontes C feita pelo Codex, PR #4), da qual depende.

Este documento registra como as páginas das aulas foram produzidas, o que foi encontrado nos PDFs e o que se recomenda para os fontes. As páginas estão em [`aulas/`](../../aulas/README.md).

## 1. Resultado

| Item | Quantidade |
|---|---:|
| PDFs inventariados ([inventário](../INVENTARIO_PDFS.md)) | 20 |
| PDFs de aula transcritos integralmente | 11 |
| Slides transcritos, um a um, na ordem original | 782 |
| Figuras preservadas, extraídas dos PDFs sem recompressão | 189 |
| Trechos de código copiados dos fontes por *script* | 103 |
| Exemplos de execução reais, conferidos com os cenários revisados | 108 |
| Explicações complementares (seção 4 das páginas) | 90 |
| Diagramas Mermaid | 18 |
| Observações técnicas (seção 8) | 133 |
| Exercícios propostos (seção 9.2) | 62 |
| Linhas da [matriz de rastreabilidade](../MATRIZ_RASTREABILIDADE.md) (uma por slide) | 782 |

Arquivos criados ou alterados:

- `aulas/aula-01/README.md` a `aulas/aula-11/README.md`, com as figuras em `aulas/aula-NN/figuras/`; a antiga `aulas/aula-09.md` foi movida para `aulas/aula-09/README.md` e reescrita no mesmo formato das demais;
- [`aulas/README.md`](../../aulas/README.md) (índice geral), [`docs/INVENTARIO_PDFS.md`](../INVENTARIO_PDFS.md), [`docs/MATRIZ_RASTREABILIDADE.md`](../MATRIZ_RASTREABILIDADE.md) e este relatório;
- [`scripts/documentacao_aulas.py`](../../scripts/documentacao_aulas.py) e [`tests/test_documentacao_aulas.py`](../../tests/test_documentacao_aulas.py);
- [`docs/MAPA_FONTES_C.md`](../MAPA_FONTES_C.md) e [`CATALOGO_FONTES.json`](CATALOGO_FONTES.json): cada fonte aponta para a seção da página da aula que o explica;
- [`README.md`](../../README.md) e as tarefas em [`atividades/`](../../atividades/README.md): *links* para as páginas das aulas;
- nos 98 fontes, **apenas comentários**: a linha `Aula:` do cabeçalho e três comentários corrigidos ([seção 6.1](#61-comentários-alterados-nos-fontes)). Nenhuma linha de código executável foi alterada.

## 2. Método

### 2.1 Inventário e classificação

Os 20 PDFs do repositório foram listados com número de páginas, tamanho e SHA-256 ([inventário](../INVENTARIO_PDFS.md)). Onze são slides de aula; oito são planos de curso do SIGAA (2021.2 a 2026.2); um é o projeto pedagógico do curso. Só os slides foram transcritos; planos e PPC foram consultados, e o plano 2026.2 forneceu a ementa e os módulos citados nas páginas. Nenhum PDF foi alterado.

### 2.2 Correspondência entre PDFs e fontes

A ligação entre slides e programas foi confirmada por três fontes independentes: (1) as capturas de código nos slides, comparadas linha a linha com a versão histórica dos fontes (commit [`04ac409`](https://github.com/Lucas-Sperotto/falect-cc-011-algoritmos-e-laboratorio-de-programacao-ii/tree/04ac4094dba3c3812809dd433a7d3855c4bffdc9), anterior à revisão de 2026); (2) as descrições das tarefas do SIGAA em [`atividades/`](../../atividades/README.md); (3) os nomes das pastas de `src/`. O resultado:

| Aula | PDF | Programas | Observação |
|---|---|---|---|
| 1 | `Aula_1.pdf` (91) | `Fontes_Aula_1/` Prog1–Prog12 | — |
| 2 | `Aula_2.pdf` (58) | `Fontes_Aula_1/` Prog13–Prog25 | a pasta histórica tem o nome da Aula 1 |
| 3 | `Aula_3.pdf` (79) | `Fontes_Aula_3_e_4/` Prog1–Prog5 e `BitTest.c` | `BitTest.c` corresponde ao slide 78 e não tem tarefa SIGAA |
| 4 | `Aula_4.pdf` (56) | `Fontes_Aula_3_e_4/` Prog6–Prog13 | o `Prog8.c` dos slides 23–26 não está no repositório ([3.2](#32-entre-o-material-e-o-repositório)) |
| 5 | `Aula_5.pdf` (74) | `Fontes_Aula_5_6_7_e_8/` Prog1–Prog7 | — |
| 6 | `Aula_6.pdf` (70) | `Fontes_Aula_5_6_7_e_8/` Prog8–Prog17 | — |
| 7 | `Aula_7.pdf` (69) | `Fontes_Aula_5_6_7_e_8/` Prog18–Prog28 | — |
| 8 | `Aula_8.pdf` (66) | `Fontes_Aula_5_6_7_e_8/` Prog29–Prog35 | — |
| 9 | `Aula_9.pdf` (33) | `Fontes_Aula_9/` Prog1–Prog4 | título da capa diferente do conteúdo; sem tarefa SIGAA |
| 10 | `Aula_10.pdf` (79) | `Fontes_Aula_10_e_11/` Prog1–Prog10 | — |
| 11 | `Aula_11.pdf` (107) | `Fontes_Aula_10_e_11/` Prog11, Prog13–Prog20 | `Prog12.c` repete `Prog11.c` e não aparece nos slides |

Os 98 fontes ficaram associados a exatamente uma aula; a tabela da seção 6 de cada página lista os seus, e a [matriz](../MATRIZ_RASTREABILIDADE.md) mostra, para cada slide, a seção da página e o programa relacionado.

### 2.3 Transcrição

O texto de cada slide foi extraído com PyMuPDF, preservando a hierarquia de tópicos, e conferido visualmente contra a imagem renderizada de todos os slides. As convenções, explicadas no início de cada página, são:

- o conteúdo do PDF fica em blocos de citação, na ordem original, com uma âncora por slide (`#slide-N`); tudo o que está fora deles foi acrescentado nesta documentação;
- erros de grafia do original são mantidos e marcados com `[sic]` (66 ocorrências); omissões de acento foram mantidas sem marcação;
- slides de roteiro repetidos são indicados por uma linha que remete ao primeiro roteiro; o rodapé repetido foi omitido;
- trechos curtos de código em imagem foram transcritos como texto; tabelas em imagem, como tabelas Markdown, com a imagem original em um bloco recolhível; diagramas foram preservados como imagem, com descrição textual;
- capturas de programas inteiros foram preservadas como imagem, com *link* para o fonte revisado e para a versão histórica em texto. Assim, o código não é digitado à mão nem existe em duas versões mantidas separadamente;
- nada foi inventado: figuras em branco ou cortadas estão marcadas como *Lacuna*, e as inferências feitas a partir do programa estão identificadas como inferências.

### 2.4 Código e execuções gerados por *script*

[`scripts/documentacao_aulas.py`](../../scripts/documentacao_aulas.py) mantém as partes das páginas que dependem de outros arquivos. Elas ficam entre marcadores HTML e são sempre regeneradas, nunca editadas à mão:

- `<!-- codigo: fonte funcao=nome -->` ou `de=…/ate=…`: copia uma função ou um trecho do fonte real, com *link* para as linhas exatas;
- `<!-- execucao: fonte cenario=nome -->`: compila o fonte com `gcc -std=c11 -Wall -Wextra -Wpedantic -O0`, executa um cenário revisado de [`cenarios_fontes_c.json`](../../scripts/cenarios_fontes_c.json) num diretório temporário e mostra comando, entradas, saídas, arquivos e código de saída. Antes de publicar, o resultado é conferido com as asserções do cenário usando a própria função do [auditor](../../scripts/auditar_fontes_c.py);
- as figuras são extraídas dos PDFs byte a byte, e a matriz é gerada a partir das páginas.

### 2.5 Validação

`python3 scripts/documentacao_aulas.py validar` confere: figuras idênticas às imagens dos PDFs; trechos de código e execuções iguais ao que o *script* gera (com endereços de memória normalizados); matriz atualizada; as dez seções numeradas em cada página; todos os slides presentes, uma vez, na ordem, com o título do PDF; nenhum marcador pendente; e todos os *links* relativos e âncoras de todos os arquivos Markdown do repositório, inclusive `#Lx-Ly` em fontes e `#page=N` em PDFs. Os testes em [`tests/test_documentacao_aulas.py`](../../tests/test_documentacao_aulas.py) cobrem as partes do *script*. O resultado da última execução está na [seção 7](#7-verificação-final).

<a id="lacunas"></a>
## 3. Relatório de lacunas

### 3.1 Nos PDFs

| Aula | Slide(s) | Lacuna | Tratamento |
|---|---|---|---|
| 3 | 4 | Frase truncada: “O problema de agrupar dados de variáveis que agrupam dados geralmente desiguais; …” | mantida como está; [nota e observação 8.1](../../aulas/aula-03/README.md#obs-3-1) |
| 5 | 40 | Frase incompleta: “Uma vez conhecidos os endereços e os tipos das variáveis como também ler o valor já armazenado nelas.” | mantida; sentido provável na [observação 8.6](../../aulas/aula-05/README.md#obs-5-6) |
| 8 | 2 | O roteiro anuncia “Alocando e desalocando memória do heap”, mas nenhum slide tem esse título | [nota no slide 2](../../aulas/aula-08/README.md#slide-2); o assunto está nos slides 7–14 |
| 9 | 1 | A capa anuncia “Ponteiros avançados”; todo o conteúdo é sobre operadores bit a bit | [observação 8.1](../../aulas/aula-09/README.md#obs-9-1) |
| 11 | 16 | Figura em branco (204 × 16 pixels) onde deveria estar a instrução `fopen` | *Lacuna*; instrução inferida do programa e identificada como inferência ([slide 16](../../aulas/aula-11/README.md#slide-16)) |
| 11 | 18 | Figura cortada (`fseek(fptr,0,`); o texto anuncia a instrução que esvazia o *buffer* (`fflush`) | *Lacuna*; transcrito só o visível ([slide 18](../../aulas/aula-11/README.md#slide-18)) |
| 11 | 20 e 24 | Figuras em branco (132 × 17 pixels, idênticas byte a byte) onde deveria estar `fseek(fptr,0,0);` | *Lacuna*; instrução inferida ([slides 20](../../aulas/aula-11/README.md#slide-20) e [24](../../aulas/aula-11/README.md#slide-24)) |

Os erros de conteúdo dos slides (afirmações imprecisas, código com defeito, dependências do Windows) não são lacunas: estão comentados nas seções 8 das páginas, resumidos na [seção 5](#5-erros-e-imprecisões-do-material).

### 3.2 Entre o material e o repositório

| Situação | Detalhe | Decisão necessária |
|---|---|---|
| Programa dos slides ausente | Aula 4, slides 23–26: `Prog8.c` com `union Numero`, `enum DataType`, `StrTipo`, `FloatTipo`, `IntTipo` e `Print`. O `Prog8.c` do repositório (A03-04-P08) contém a união `uInit` dos slides 32–34; a descrição do SIGAA (“Mostra o uso de uniões”) corresponde ao programa dos slides | incluir o programa dos slides como novo fonte, ou registrar a diferença no fonte ([R5](#r5)) |
| Programa repetido | Aula 11: `Prog12.c` (A10-11-P12) é igual a `Prog11.c`, não aparece nos slides, mas está na tarefa do SIGAA com outra descrição | definir o papel de `Prog12.c` ([R11](#r11)) |
| Fonte sem tarefa | `BitTest.c` (A03-04-BITTEST), slide 78 da Aula 3 | nenhuma; documentado na Aula 3 |
| Aula sem tarefa | Aula 9 não tem tarefa SIGAA transcrita | confirmar no SIGAA |
| Tarefa sem fontes | A [revisão de 21/09/2026](../../atividades/revisao-2026-09-21.md) pede cinco programas que não estão em `src/` | incluir os fontes, se existirem |

<a id="ementa"></a>
### 3.3 Itens da ementa 2026.2 sem aula própria

| Item | Situação nesta documentação |
|---|---|
| Recursividade | sem slides; complemento na [Aula 7, seção 4.8](../../aulas/aula-07/README.md#c-7-8) (busca binária recursiva) |
| Biblioteca STL | não tratada: pertence ao C++, e o material usa C |
| Inserção e remoção em vetores | sem slides; [exercício 4 da Aula 1](../../aulas/aula-01/README.md#92-exercícios-propostos-acréscimo-desta-documentação) |
| Variáveis locais e globais | sem slides próprios; complemento na [Aula 3, seção 4.7](../../aulas/aula-03/README.md#c-3-7) |
| Módulo 3 (prática de programação e algoritmos) | não há PDF de aula correspondente |

A cobertura completa da ementa está no [índice das aulas](../../aulas/README.md#cobertura-da-ementa-20262).

### 3.4 Limites desta documentação

- As capturas de programas inteiros não foram redigitadas: a página remete à versão histórica em texto e ao fonte revisado. Nos slides 23–26 da Aula 4, cujo programa não existe no repositório, as capturas são a única fonte e foram descritas em texto.
- Os exemplos de execução foram gerados no Linux (WSL, GCC 13.3, glibc 2.39). No Windows, programas que dependem de modo texto, de `conio.h` ou de nomes de dispositivos se comportariam como nos slides, e não como nos exemplos.
- Os diagramas Mermaid são exibidos pelo GitHub; em outros visualizadores aparecem como código.

## 4. Decisões tomadas

- **Numeração das aulas:** segue os PDFs (`Aula_1.pdf` a `Aula_11.pdf`), e não as pastas de `src/`, cujos nomes agrupam aulas.
- **Página da Aula 9:** a página anterior (`aulas/aula-09.md`) foi movida para `aulas/aula-09/README.md` e refeita no formato comum; as informações que ela trazia foram incorporadas.
- **Código histórico × revisado:** as figuras mostram o código dos slides; os trechos em texto são sempre do fonte revisado, e cada página explica as diferenças ([seção 6 de qualquer aula](../../aulas/aula-11/README.md#6-programas-c-da-aula)).
- **Inferências:** só aparecem fora dos blocos de citação e com a palavra “inferência”, como nas figuras em branco da Aula 11.
- **Linha `Aula:` dos fontes:** passou a apontar para a página da aula, e não para a tarefa do SIGAA; a tarefa continua listada em `references` no catálogo e no [mapa dos fontes](../MAPA_FONTES_C.md).

## 5. Erros e imprecisões do material

As 133 observações técnicas das páginas registram, slide a slide, o que no material está impreciso, desatualizado ou depende do Windows. Os grupos mais frequentes:

| Tipo | Exemplos |
|---|---|
| Funções inseguras ou removidas | `gets()` em várias aulas (removida no C11); `scanf("%s")` sem largura ([Aula 2, 8.3](../../aulas/aula-02/README.md#obs-2-3)) |
| Dependências do Windows/DOS | `conio.h` (`getch`, `getche`), `system("pause")`, `system("TYPE …")`, `io.h`, `O_BINARY`, impressora `PRN`, ANSI.SYS ([Aula 8, 8.8](../../aulas/aula-08/README.md#obs-8-8)) |
| Afirmações imprecisas | ponteiros locais “inicializados com `NULL`” ([Aula 5, 8.7](../../aulas/aula-05/README.md#obs-5-7)); `M + i` ≡ `M[i]` ([Aula 2, 8.8](../../aulas/aula-02/README.md#obs-2-8)); o operador `~=` ([Aula 9, 8.3](../../aulas/aula-09/README.md#obs-9-3)); `putc`/`fputc` invertidos ([Aula 10, 8.3](../../aulas/aula-10/README.md#obs-10-3)); tamanho de `Livro` 110 × 112 ([Aula 11, 8.2](../../aulas/aula-11/README.md#obs-11-2)) |
| Defeitos nos programas dos slides | `while(!feof(...))` que repete a última leitura ([Aula 10, 8.5](../../aulas/aula-10/README.md#obs-10-5); [Aula 11, 8.6](../../aulas/aula-11/README.md#obs-11-6)); `nrec - 1` no lugar de `rec - 1` ([Aula 11, 8.5](../../aulas/aula-11/README.md#obs-11-5)); terminador uma posição adiante ([Aula 11, 8.9](../../aulas/aula-11/README.md#obs-11-9)); busca fora dos limites do *buffer* ([Aula 11, 8.14](../../aulas/aula-11/README.md#obs-11-14)); cópia que apaga a origem ([Aula 11, 8.15](../../aulas/aula-11/README.md#obs-11-15)) |
| Mudanças da linguagem | `int` implícito e `const true=1;` com C23 ([Aula 7, 8.4](../../aulas/aula-07/README.md#obs-7-4)) |

Os fontes revisados pelo Codex já corrigem os defeitos dos programas; as páginas mostram as duas versões e explicam a diferença. Afirmações que pareciam verificáveis foram testadas antes de entrar nas páginas (por exemplo, a saída de `strcmp` com e sem *builtins* do GCC, o efeito de `-O2` sobre a espera ativa, a repetição da última linha em `Prog16.c`, o byte residual em `Prog18.c` e o comportamento de `rewind(stdin)` com arquivo e com *pipe*).

<a id="recomendacoes"></a>
## 6. Recomendações para os fontes

### 6.1 Comentários alterados nos fontes

Alterações só em comentários, feitas nesta documentação. O número de linhas de cada arquivo não mudou.

| Fonte | Alteração | Motivo |
|---|---|---|
| os 98 fontes | linha `Aula:` do cabeçalho aponta para `aulas/aula-NN/README.md` | a página da aula passou a existir; a página da Aula 9 mudou de lugar |
| [`Fontes_Aula_3_e_4/BitTest.c`](../../src/Fontes_Aula_3_e_4/BitTest.c) (A03-04-BITTEST) | objetivo “Bits 0 a 7” → “Campos de bits: caractere e atributos de vídeo em 16 bits.” (também no catálogo) | o texto anterior era o primeiro comentário do código e não descrevia o programa |
| [`Fontes_Aula_10_e_11/Prog9.c`](../../src/Fontes_Aula_10_e_11/Prog9.c) (A10-11-P09) | “Linux não traduz CRLF em modo texto” → “Modo binário: sem tradução de fim de linha” | o comentário fora copiado de `Prog8.c`, que usa modo texto |
| [`Fontes_Aula_5_6_7_e_8/Prog18.c`](../../src/Fontes_Aula_5_6_7_e_8/Prog18.c) (A05-08-P18) | “dar um tempo” → “dar um tempo (espera ativa: o otimizador pode removê-la)” | com `-O2`, o GCC elimina o laço vazio ([Aula 7, 8.13](../../aulas/aula-07/README.md#obs-7-13)) |

### 6.2 Encaminhadas ao Codex

Estas sugestões mudam código ou comportamento e, por isso, não foram aplicadas. Cada uma indica o programa, o problema e a justificativa.

<a id="r1"></a>
**R1 — A01-P04 e A01-P05 ([`Fontes_Aula_1/Prog4.c`](../../src/Fontes_Aula_1/Prog4.c), [`Prog5.c`](../../src/Fontes_Aula_1/Prog5.c)).** Os slides 22–33 da Aula 1 mostram uma progressão: `Prog4.c` lê notas com `do-while` sem verificar o limite do vetor, e `Prog5.c` acrescenta a verificação. Os fontes revisados são quase idênticos (os dois verificam o limite) e trocaram o `do-while` por `while` com `break`. *Sugestão:* manter em `Prog4.c` a estrutura `do-while` e deixar visível, em comentário ou em código, a ausência de verificação que `Prog5.c` corrige. *Justificativa:* preservar a intenção pedagógica ([Aula 1, 8.5](../../aulas/aula-01/README.md#obs-1-5)).

<a id="r2"></a>
**R2 — A01-P15 e A01-P17 ([`Fontes_Aula_1/Prog15.c`](../../src/Fontes_Aula_1/Prog15.c), [`Prog17.c`](../../src/Fontes_Aula_1/Prog17.c)).** Chamam `strlen` sem `#include <string.h>`; compilam porque `entrada_segura.h` inclui esse cabeçalho. *Sugestão:* incluir `<string.h>` nos dois. *Justificativa:* cada fonte deve declarar o que usa ([Aula 2, 8.17](../../aulas/aula-02/README.md#obs-2-17)).

<a id="r3"></a>
**R3 — A03-04-P04 ([`Fontes_Aula_3_e_4/Prog4.c`](../../src/Fontes_Aula_3_e_4/Prog4.c)).** Com peças ou preços fora do domínio, o programa termina com `EXIT_FAILURE` sem mensagem. *Sugestão:* explicar o motivo em `stderr`. *Justificativa:* o usuário não sabe por que o programa falhou ([Aula 3, 8.9](../../aulas/aula-03/README.md#obs-3-9)).

<a id="r4"></a>
**R4 — A03-04-P05 ([`Fontes_Aula_3_e_4/Prog5.c`](../../src/Fontes_Aula_3_e_4/Prog5.c)).** Uma venda com dados inválidos é descartada sem aviso (cenário `venda-dia-invalido`). *Sugestão:* informar a rejeição. *Justificativa:* o mesmo da R3 ([Aula 3, 8.7](../../aulas/aula-03/README.md#obs-3-7)).

<a id="r5"></a>
**R5 — A03-04-P08 ([`Fontes_Aula_3_e_4/Prog8.c`](../../src/Fontes_Aula_3_e_4/Prog8.c)).** O programa dos slides 23–26 da Aula 4 não está no repositório, e o arquivo com esse nome contém outro exemplo ([3.2](#32-entre-o-material-e-o-repositório)). *Sugestão:* decidir com o professor se o programa dos slides deve ser recriado a partir das capturas (como novo fonte, com ID próprio) e, em qualquer caso, registrar a diferença no comentário de `Prog8.c`. *Justificativa:* a tarefa do SIGAA descreve o programa dos slides ([Aula 4, 8.6](../../aulas/aula-04/README.md#obs-4-6)).

<a id="r6"></a>
**R6 — A05-08-P17 ([`Fontes_Aula_5_6_7_e_8/Prog17.c`](../../src/Fontes_Aula_5_6_7_e_8/Prog17.c)).** As posições vazias da matriz valem 0 e são impressas com `%c`, ou seja, como bytes nulos. *Sugestão:* inicializar a matriz com espaços ou imprimir `' '` no lugar de 0. *Justificativa:* bytes nulos não são texto; aparecem de forma diferente em cada terminal e atrapalham redirecionamentos ([Aula 6, seção 6.10](../../aulas/aula-06/README.md#a05-08-p17)).

<a id="r7"></a>
**R7 — A05-08-P20 a A05-08-P22 ([`Prog20.c`](../../src/Fontes_Aula_5_6_7_e_8/Prog20.c), [`Prog21.c`](../../src/Fontes_Aula_5_6_7_e_8/Prog21.c), [`Prog22.c`](../../src/Fontes_Aula_5_6_7_e_8/Prog22.c)).** `const int true=1;` é válido em C11, mas `true` é palavra-chave no C23, padrão do GCC 15. *Sugestão:* trocar o nome (por exemplo, `VERDADEIRO`) ou usar `while (1)`. *Justificativa:* os programas deixam de compilar sem `-std=c11` ([Aula 7, 8.4](../../aulas/aula-07/README.md#obs-7-4)).

<a id="r8"></a>
**R8 — A05-08-P18 ([`Fontes_Aula_5_6_7_e_8/Prog18.c`](../../src/Fontes_Aula_5_6_7_e_8/Prog18.c)).** A pausa por laço vazio desaparece com otimização e depende da máquina. *Sugestão:* manter o laço como ilustração (o comentário já avisa) ou usar `nanosleep()`/`thrd_sleep()`. *Justificativa:* comportamento observável diferente entre `-O0` e `-O2` ([Aula 7, 8.13](../../aulas/aula-07/README.md#obs-7-13)).

<a id="r9"></a>
**R9 — A10-11-P02 e A10-11-P03 ([`Fontes_Aula_10_e_11/Prog2.c`](../../src/Fontes_Aula_10_e_11/Prog2.c), [`Prog3.c`](../../src/Fontes_Aula_10_e_11/Prog3.c)).** Nos slides, `Prog2.c` não verifica a abertura e `Prog3.c` mostra a correção; os fontes revisados são idênticos a partir do cabeçalho. *Sugestão:* deixar em `Prog2.c` a ausência de verificação visível, em comentário. *Justificativa:* o contraste dos slides 39–41 deixou de existir no código ([Aula 10, seção 6.2](../../aulas/aula-10/README.md#a10-11-p02)).

<a id="r10"></a>
**R10 — A10-11-P04 ([`Fontes_Aula_10_e_11/Prog4.c`](../../src/Fontes_Aula_10_e_11/Prog4.c)).** As seis chamadas `fputs` do slide 44 viraram uma só, com literais concatenados. *Sugestão:* voltar às seis chamadas. *Justificativa:* o slide 46 explica justamente uma chamada por linha ([Aula 10, seção 6.4](../../aulas/aula-10/README.md#a10-11-p04)).

<a id="r11"></a>
**R11 — A10-11-P11 e A10-11-P12 ([`Prog11.c`](../../src/Fontes_Aula_10_e_11/Prog11.c), [`Prog12.c`](../../src/Fontes_Aula_10_e_11/Prog12.c)).** Os dois arquivos são iguais; `Prog12.c` não aparece nos slides. *Sugestão:* confirmar com o professor o que a tarefa do SIGAA espera em `Prog12.c` e, se for só uma repetição, dizer isso no comentário inicial. *Justificativa:* evitar que o estudante procure uma diferença inexistente ([Aula 11, seção 6.2](../../aulas/aula-11/README.md#a10-11-p12)).

<a id="r12"></a>
**R12 — A10-11-P19 ([`Fontes_Aula_10_e_11/Prog19.c`](../../src/Fontes_Aula_10_e_11/Prog19.c)), opcional.** O contexto exibido depois da frase se limita aos bytes já lidos quando ela é encontrada. *Sugestão:* ler mais um bloco antes de imprimir, para mostrar os 100 bytes prometidos no slide 90. *Justificativa:* coerência com o enunciado; não é um defeito de memória ([Aula 11, seção 6.9](../../aulas/aula-11/README.md#a10-11-p19)).

<a id="r13"></a>
**R13 — A09-P04 ([`Fontes_Aula_9/Prog4.c`](../../src/Fontes_Aula_9/Prog4.c)), opcional.** O complemento, operador unário, ainda exige um segundo operando fictício (`FFFF ~ 0`). *Sugestão:* aceitar a forma `~ FFFF`. *Justificativa:* a entrada atual reforça a ideia equivocada de um `~` binário, já comentada na [Aula 9, 8.3](../../aulas/aula-09/README.md#obs-9-3).

## 7. Verificação final

Comandos executados no ambiente de referência (WSL2, Linux 6.18, GCC 13.3, Python 3.12, glibc 2.39):

```bash
python3 scripts/documentacao_aulas.py validar      # páginas, figuras, código, execuções, matriz e links
python3 -m unittest discover -s tests -v           # testes do script de documentação e do auditor
python3 scripts/verificar_fontes_c.py              # cabeçalhos e catálogo dos fontes
python3 scripts/auditar_fontes_c.py --executar     # cenários revisados (auditor do Codex)
bash script.sh                                     # compilação de todos os fontes
```

Resultados em 30/10/2026:

| Verificação | Resultado |
|---|---|
| `documentacao_aulas.py validar` (com as 108 execuções) | 0 problemas, 0 avisos |
| Testes unitários (`tests/`) | 20 de 20 aprovados |
| `verificar_fontes_c.py` | 98 fontes, 0 erros, 0 avisos |
| Auditor do Codex, cenários revisados | 98 fontes compilados sem avisos; 277 de 277 cenários aprovados |
| Auditor do Codex com ASan e UBSan (`--sanitizers`) | 277 de 277 cenários aprovados |

Os *links* para trechos de código usam números de linha dos fontes atuais. Se um fonte mudar, `python3 scripts/documentacao_aulas.py codigo` e `execucoes` regeneram as páginas, e `validar` aponta o que ficou desatualizado.
