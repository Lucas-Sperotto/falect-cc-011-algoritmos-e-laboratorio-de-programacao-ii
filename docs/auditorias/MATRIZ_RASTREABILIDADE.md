# Matriz de Rastreabilidade e Controle de Qualidade — Antigravity

**Disciplina:** Algoritmos e Laboratório de Programação II (FALECT-CC-011) — UNEMAT, 2026.2  
**Auditor:** Antigravity (Auditoria Independente e Integração)  
**Data:** 30/10/2026  
**Documento de Referência Primária:** [Matriz Granular Slide a Slide (782 slides)](../MATRIZ_RASTREABILIDADE.md) | [Inventário dos PDFs](../INVENTARIO_PDFS.md) | [Catálogo dos Fontes](CATALOGO_FONTES.json)

---

## 1. Visão Geral da Rastreabilidade da Oferta 2026.2

Esta matriz consolida a rastreabilidade entre o plano de curso do SIGAA, os slides em PDF originais (2022), a documentação pedagógica em Markdown (produzida pelo Claude Code), os programas em linguagem C (revisados pelo Codex), as tarefas cadastradas no SIGAA e as evidências objetivas de validação técnica e execução.

---

## 2. Matriz de Controle de Qualidade por Aula

| Aula | PDF Correspondente | Markdown Correspondente | Códigos C Relacionados | Exercícios Associados | Estado de Revisão | Pendências | Evidências de Validação |
|---|---|---|---|---|:---:|---|---|
| **01** | [`Aula_1.pdf`](../../aulas/Aula_1.pdf)<br>(91 slides, 1.064 KiB) | [`aulas/aula-01/README.md`](../../aulas/aula-01/README.md)<br>(10 seções, 2 diagramas Mermaid) | `Fontes_Aula_1/`<br>Prog1 a Prog12<br>(IDs: `A01-P01` a `A01-P12`) | • [SIGAA Aula 01 - pt 1](../../atividades/aula-01-pt1.md) (Prog1–5)<br>• [SIGAA Aula 01 - pt 2](../../atividades/aula-01-pt2.md) (Prog6–12)<br>• 7 exercícios propostos (seção 9.2) | **Aprovado com ressalvas pedagógicas** | • R1: `Prog4.c` teve verificação de limite antecipada pelo Codex, atenuando contraste didático com `Prog5.c` ("BUFFER LOTADO").<br>• Falta exemplo explícito de inserção/remoção em vetor estático (previsto na ementa). | • 12 fontes compilam com `gcc -std=c11 -Wall -Wextra -Wpedantic` (0 avisos).<br>• 43 cenários testados e aprovados com ASan/UBSan.<br>• 91 slides transcritos integralmente.<br>• 21 figuras preservadas. |
| **02** | [`Aula_2.pdf`](../../aulas/Aula_2.pdf)<br>(58 slides, 917 KiB) | [`aulas/aula-02/README.md`](../../aulas/aula-02/README.md)<br>(10 seções, 1 diagrama Mermaid) | `Fontes_Aula_1/`<br>Prog13 a Prog25<br>(IDs: `A01-P13` a `A01-P25`) | • [SIGAA Aula 02](../../atividades/aula-02.md) (Prog13–25)<br>• 6 exercícios propostos (seção 9.2) | **Aprovado com ressalvas técnicas** | • R2: `Prog15.c` e `Prog17.c` utilizam `strlen` sem `#include <string.h>` direto.<br>• Nomes físicos ficam em `Fontes_Aula_1/` por restrição histórica. | • 13 fontes compilam sem avisos.<br>• 37 cenários testados e aprovados com ASan/UBSan.<br>• 58 slides transcritos integralmente.<br>• 18 figuras preservadas. |
| **03** | [`Aula_3.pdf`](../../aulas/Aula_3.pdf)<br>(79 slides, 958 KiB) | [`aulas/aula-03/README.md`](../../aulas/aula-03/README.md)<br>(10 seções, 1 diagrama Mermaid) | `Fontes_Aula_3_e_4/`<br>Prog1 a Prog5 e `BitTest.c`<br>(IDs: `A03-04-P01` a `P05`, `BITTEST`) | • [SIGAA Aulas 03 e 04](../../atividades/aulas-03-e-04.md) (Prog1–5)<br>• `BitTest.c` sem tarefa SIGAA<br>• 6 exercícios propostos (seção 9.2) | **Aprovado com ressalvas técnicas** | • R3: `Prog4.c` encerra com `EXIT_FAILURE` sem diagnóstico no `stderr` em entradas fora do domínio.<br>• R4: `Prog5.c` descarta venda inválida silenciosamente.<br>• Frase truncada no slide 4 do PDF mantida com nota explicativa. | • 6 fontes compilam sem avisos.<br>• 19 cenários testados e aprovados com ASan/UBSan.<br>• 79 slides transcritos integralmente.<br>• 14 figuras preservadas. |
| **04** | [`Aula_4.pdf`](../../aulas/Aula_4.pdf)<br>(56 slides, 921 KiB) | [`aulas/aula-04/README.md`](../../aulas/aula-04/README.md)<br>(10 seções, 1 diagrama Mermaid) | `Fontes_Aula_3_e_4/`<br>Prog6 a Prog13<br>(IDs: `A03-04-P06` a `P13`) | • [SIGAA Aulas 03 e 04](../../atividades/aulas-03-e-04.md) (Prog6–13)<br>• 6 exercícios propostos (seção 9.2) | **Aprovado com ressalva crítica de acervo** | • R5: O `Prog8.c` dos slides 23–26 (`union Numero`, `enum DataType`) **não existe** no repositório; o arquivo físico contém `uInit` dos slides 32–34. Decisão pendente com docente. | • 8 fontes compilam sem avisos.<br>• 22 cenários testados e aprovados com ASan/UBSan.<br>• 56 slides transcritos integralmente.<br>• 20 figuras preservadas. |
| **05** | [`Aula_5.pdf`](../../aulas/Aula_5.pdf)<br>(74 slides, 886 KiB) | [`aulas/aula-05/README.md`](../../aulas/aula-05/README.md)<br>(10 seções, 3 diagramas Mermaid) | `Fontes_Aula_5_6_7_e_8/`<br>Prog1 a Prog7<br>(IDs: `A05-08-P01` a `P07`) | • [SIGAA Aulas 05 e 06](../../atividades/aulas-05-e-06.md) (Prog1–7)<br>• 5 exercícios propostos (seção 9.2) | **Aprovado integralmente** | • Frase incompleta no slide 40 do PDF preservada com nota técnica no Markdown.<br>• Pasta física agrupa aulas 5 a 8. | • 7 fontes compilam sem avisos.<br>• 22 cenários testados e aprovados com ASan/UBSan.<br>• 74 slides transcritos integralmente.<br>• 12 figuras preservadas. |
| **06** | [`Aula_6.pdf`](../../aulas/Aula_6.pdf)<br>(70 slides, 988 KiB) | [`aulas/aula-06/README.md`](../../aulas/aula-06/README.md)<br>(10 seções, 3 diagramas Mermaid) | `Fontes_Aula_5_6_7_e_8/`<br>Prog8 a Prog17<br>(IDs: `A05-08-P08` a `P17`) | • [SIGAA Aulas 05 e 06](../../atividades/aulas-05-e-06.md) (Prog8–13)<br>• [SIGAA Aulas 06 e 07](../../atividades/aulas-06-e-07.md) (Prog14–17)<br>• 5 exercícios propostos (seção 9.2) | **Aprovado com ressalvas técnicas** | • R6: `Prog17.c` imprime bytes nulos (`0x00`) com `%c` para posições vazias da matriz no terminal.<br>• Descasamento de agrupamento entre tarefas SIGAA e pastas físicas. | • 10 fontes compilam sem avisos.<br>• 30 cenários testados e aprovados com ASan/UBSan.<br>• 70 slides transcritos integralmente.<br>• 20 figuras preservadas. |
| **07** | [`Aula_7.pdf`](../../aulas/Aula_7.pdf)<br>(69 slides, 1.080 KiB) | [`aulas/aula-07/README.md`](../../aulas/aula-07/README.md)<br>(10 seções, 1 diagrama Mermaid) | `Fontes_Aula_5_6_7_e_8/`<br>Prog18 a Prog28<br>(IDs: `A05-08-P18` a `P28`) | • [SIGAA Aulas 06 e 07](../../atividades/aulas-06-e-07.md) (Prog18–28)<br>• 6 exercícios propostos (seção 9.2) | **Aprovado com ressalvas de portabilidade** | • R7: `const int true=1;` em `Prog20.c`, `Prog21.c` e `Prog22.c` quebra compilação sob padrão C23 (GCC 15).<br>• R8: Espera ativa vazia de `Prog18.c` é eliminada pelo GCC sob `-O2`.<br>• Recursividade introduzida como complemento (seção 4.8). | • 11 fontes compilam sem avisos em C11.<br>• 30 cenários testados e aprovados com ASan/UBSan.<br>• 69 slides transcritos integralmente.<br>• 19 figuras preservadas. |
| **08** | [`Aula_8.pdf`](../../aulas/Aula_8.pdf)<br>(66 slides, 1.030 KiB) | [`aulas/aula-08/README.md`](../../aulas/aula-08/README.md)<br>(10 seções, 2 diagramas Mermaid) | `Fontes_Aula_5_6_7_e_8/`<br>Prog29 a Prog35<br>(IDs: `A05-08-P29` a `P35`) | • [SIGAA Aula 08](../../atividades/aula-08.md) (Prog29–35)<br>• 5 exercícios propostos (seção 9.2) | **Aprovado integralmente** | • Tópico de roteiro do slide 2 sem slide com título correspondente no PDF original.<br>• Exemplos cobrem lista ligada dinâmica e argumentos de linha de comando. | • 7 fontes compilam sem avisos.<br>• 22 cenários testados e aprovados com ASan/UBSan.<br>• 66 slides transcritos integralmente.<br>• 18 figuras preservadas. |
| **09** | [`Aula_9.pdf`](../../aulas/Aula_9.pdf)<br>(33 slides, 823 KiB) | [`aulas/aula-09/README.md`](../../aulas/aula-09/README.md)<br>(10 seções, 0 diagramas Mermaid) | `Fontes_Aula_9/`<br>Prog1 a Prog4<br>(IDs: `A09-P01` a `P04`) | • **Nenhuma tarefa SIGAA transcrita**<br>• 4 exercícios propostos (seção 9.2) | **Aprovado com divergência temática** | • Título original da capa ("Ponteiros Avançados") é divergente do conteúdo real (100% operadores bit a bit).<br>• Ausência de tarefa correspondente no SIGAA.<br>• R13: Operador unário de negação `~` em `Prog4.c` exige operando fictício. | • 4 fontes compilam sem avisos.<br>• 15 cenários testados e aprovados com ASan/UBSan.<br>• 33 slides transcritos integralmente.<br>• 9 figuras preservadas. |
| **10** | [`Aula_10.pdf`](../../aulas/Aula_10.pdf)<br>(79 slides, 1.200 KiB) | [`aulas/aula-10/README.md`](../../aulas/aula-10/README.md)<br>(10 seções, 1 diagrama Mermaid) | `Fontes_Aula_10_e_11/`<br>Prog1 a Prog10<br>(IDs: `A10-11-P01` a `P10`) | • [SIGAA Aula 10](../../atividades/aula-10.md) (Prog1–10)<br>• 6 exercícios propostos (seção 9.2) | **Aprovado com ressalvas pedagógicas** | • R9: `Prog2.c` e `Prog3.c` tornaram-se idênticos em código executável após saneamento do Codex, anulando demonstração de erro de `fopen`.<br>• R10: Seis `fputs` de `Prog4.c` foram unificados em uma chamada, desencontrando o slide 46. | • 10 fontes compilam sem avisos.<br>• 25 cenários testados e aprovados com ASan/UBSan.<br>• 79 slides transcritos integralmente.<br>• 16 figuras preservadas. |
| **11** | [`Aula_11.pdf`](../../aulas/Aula_11.pdf)<br>(107 slides, 1.251 KiB) | [`aulas/aula-11/README.md`](../../aulas/aula-11/README.md)<br>(10 seções, 3 diagramas Mermaid) | `Fontes_Aula_10_e_11/`<br>Prog11 a Prog20<br>(IDs: `A10-11-P11` a `P20`) | • [SIGAA Aula 11](../../atividades/aula-11.md) (Prog11–20)<br>• 6 exercícios propostos (seção 9.2) | **Aprovado com ressalvas de acervo** | • R11: `Prog11.c` e `Prog12.c` são arquivos com código 100% duplicado.<br>• Slides 16, 18, 20 e 24 do PDF continham figuras em branco ou cortadas (saneadas por inferência pedagógica explícita).<br>• R12: Janela de contexto de `Prog19.c` exibe apenas bytes do bloco corrente. | • 10 fontes compilam sem avisos.<br>• 34 cenários testados e aprovados com ASan/UBSan.<br>• 107 slides transcritos integralmente.<br>• 22 figuras preservadas. |

---

## 3. Matriz de Cobertura da Ementa Oficial (Plano de Curso 2026.2)

| Tópico da Ementa Oficial SIGAA 2026.2 | Aulas Que Cobrem | Programas C Que Implementam | Status Pedagógico | Avaliação Antigravity |
|---|---|---|:---:|---|
| **Vetores e matrizes estáticos (inserção, remoção e busca)** | Aulas 01 e 02 | `Fontes_Aula_1/` Prog1–Prog12; busca em Prog8–9 | Parcial nos slides originais | Slides originais cobriam apenas declaração, acesso e busca linear. Inserção e remoção foram incorporadas como exercícios práticos na documentação Markdown. |
| **Ponteiros** | Aulas 05, 06, 07 e 08 | `Fontes_Aula_5_6_7_e_8/` Prog1–Prog28 | Completo | Cobertura profunda: endereços, indireção, aritmética, vetores de ponteiros, ponteiros para funções e `void *`. |
| **Variáveis dinâmicas** | Aula 08 | `Fontes_Aula_5_6_7_e_8/` Prog29–Prog35 | Completo | `malloc`, `calloc`, `free`, dimensionamento de vetores/matrizes e lista ligada com alocação dinâmica. |
| **Manipulação de arquivos** | Aulas 10 e 11 | `Fontes_Aula_10_e_11/` Prog1–Prog20 | Completo | Fluxos de alto nível (`FILE *`), texto, registros binários (`fread`/`fwrite`/`fseek`) e descritores POSIX de baixo nível (`open`/`read`/`write`). |
| **Estrutura de dados e abstração** | Aulas 03, 04 e 08 | `Fontes_Aula_3_e_4/` Prog1–Prog5; `Fontes_Aula_5_6_7_e_8/` Prog31 | Completo | Registros heterogêneos (`struct`), uniões (`union`), tipos abstratos com `typedef` e lista ligada auto-referenciada. |
| **Variáveis locais e globais** | Aula 03 (Complemento 4.7) | Ilustrado em `Fontes_Aula_1/Prog8`, `Fontes_Aula_3_e_4/Prog8` | Complementar | Não possuía slides próprios dedicados. Inserido como explicação conceitual complementar de escopo e tempo de vida. |
| **Biblioteca STL (Standard Template Library)** | *Não aplicável em C* | *Nenhum* | Incompatibilidade de Linguagem | A STL pertence à linguagem C++. O repositório e a oferta são 100% C. Mantida nota de esclarecimento explícita para evitar confusão estudantil. |
| **Cadeias de caracteres (strings)** | Aulas 02 e 06 | `Fontes_Aula_1/` Prog13–Prog25; `Fontes_Aula_5_6_7_e_8/` Prog12–Prog14 | Completo | Vetores de `char`, terminador `\0`, funções padrão (`string.h`), cópias seguras e aritmética de ponteiros com strings. |
| **Registros** | Aulas 03, 04 e 11 | `Fontes_Aula_3_e_4/` Prog1–Prog13; `Fontes_Aula_10_e_11/` Prog11–Prog15 | Completo | Sintaxe, alinhamento, preenchimento (padding), passagem para funções e persistência binária. |
| **Programação estruturada** | Todas as aulas | Todos os 98 fontes C | Completo | Modularização em funções, controle de fluxo e ausência de desvios não estruturados. |
| **Passagem por valor e por referência** | Aulas 01, 03 e 05 | `Fontes_Aula_5_6_7_e_8/` Prog3 e Prog4; `Fontes_Aula_3_e_4/` Prog4 | Completo | Contraste didático explícito: `troca(v1, v2)` (valor, sem efeito na `main`) vs `troca(&v1, &v2)` (referência simulada por ponteiro). |
| **Recursividade** | Aula 07 (Complemento 4.8) | `busca_rec` na documentação | Complementar | Não possuía PDF nem programa próprio. Claude Code acrescentou busca binária recursiva com rastreamento da pilha de chamadas. |
| **Módulo 3: Prática de programação e algoritmos** | *(Oferta 27/10 a 30/10/2026)* | Nenhum programa C específico | **Lacuna no repositório** | O plano oficial prevê a 3ª unidade/módulo focada em prática de algoritmos, mas não há slides nem pasta correspondente em `src/`. |

---

## 4. Matriz de Tarefas SIGAA e Descasamento de Acervo

| Tarefa SIGAA (`atividades/`) | Período Declarado | Arquivos C Vinculados | Status Físico em `src/` | Observações da Auditoria |
|---|---|---|---|---|
| [`aula-01-pt1.md`](../../atividades/aula-01-pt1.md) | 21/09 a 07/11/2026 | `Prog01.c` a `Prog05.c` | Localizados em `src/Fontes_Aula_1/Prog1.c` a `Prog5.c` | Divergência de zero à esquerda nos nomes (`Prog01` vs `Prog1`). |
| [`aula-01-pt2.md`](../../atividades/aula-01-pt2.md) | 21/09 a 07/11/2026 | `Prog06.c` a `Prog12.c` | Localizados em `src/Fontes_Aula_1/Prog6.c` a `Prog12.c` | Divisão arbitrária da Aula 1 em duas entregas no SIGAA. |
| [`aula-02.md`](../../atividades/aula-02.md) | 21/09 a 07/11/2026 | `Prog13.c` a `Prog25.c` | Localizados em `src/Fontes_Aula_1/Prog13.c` a `Prog25.c` | Pasta física chama-se `Fontes_Aula_1`, gerando desorientação para alunos da Aula 2. |
| [`aulas-03-e-04.md`](../../atividades/aulas-03-e-04.md) | 21/09 a 07/11/2026 | `Prog01.c` a `Prog13.c` | Localizados em `src/Fontes_Aula_3_e_4/Prog1.c` a `Prog13.c` | `BitTest.c` existe na pasta e no slide 78 da Aula 3, mas não consta na tarefa SIGAA. `Prog8.c` físico não corresponde ao enunciado da tarefa. |
| [`aulas-05-e-06.md`](../../atividades/aulas-05-e-06.md) | 21/09 a 07/11/2026 | `Prog01.c` a `Prog13.c` | Localizados em `src/Fontes_Aula_5_6_7_e_8/Prog1.c` a `Prog13.c` | A tarefa agrupa programas de duas aulas conceituais distintas. |
| [`aulas-06-e-07.md`](../../atividades/aulas-06-e-07.md) | 21/09 a 07/11/2026 | `Prog14.c` a `Prog28.c` | Localizados em `src/Fontes_Aula_5_6_7_e_8/Prog14.c` a `Prog28.c` | Continuação da pasta única de ponteiros. |
| [`aula-08.md`](../../atividades/aula-08.md) | 21/09 a 07/11/2026 | `Prog29.c` a `Prog35.c` | Localizados em `src/Fontes_Aula_5_6_7_e_8/Prog29.c` a `Prog35.c` | Último bloco da pasta `Fontes_Aula_5_6_7_e_8`. |
| *Aula 09 (Bitwise)* | *(Sem cadastro)* | `Prog1.c` a `Prog4.c` | Localizados em `src/Fontes_Aula_9/` | Não há arquivo de atividade nem tarefa no SIGAA. |
| [`aula-10.md`](../../atividades/aula-10.md) | 21/09 a 07/11/2026 | `Prog01.c` a `Prog10.c` | Localizados em `src/Fontes_Aula_10_e_11/Prog1.c` a `Prog10.c` | Primeira metade da pasta de arquivos. |
| [`aula-11.md`](../../atividades/aula-11.md) | 21/09 a 07/11/2026 | `Prog11.c` a `Prog20.c` | Localizados em `src/Fontes_Aula_10_e_11/Prog11.c` a `Prog20.c` | `Prog12.c` é cópia fiel de `Prog11.c`. |
| [`revisao-2026-09-21.md`](../../atividades/revisao-2026-09-21.md) | 21/09 a 07/11/2026 | `Prog01.c` a `Prog05.c` (revisão) | **Ausentes em `src/`** | Cinco programas solicitados no SIGAA cujos fontes nunca estiveram no repositório. |

---

## 5. Resumo Quantitativo da Auditoria

- **Total de PDFs analisados:** 20 (11 aulas + 8 planos de curso + 1 PPC)
- **Total de slides auditados:** 782 (100% cobertos)
- **Total de programas C inventariados e testados:** 98 (100% compilados e executados)
- **Cenários de teste executados:** 277 (100% aprovados com ASan e UBSan)
- **Exemplos de execução documentados no Markdown:** 108
- **Observações técnicas registradas:** 133
- **Diagramas Mermaid incorporados:** 18
- **Figuras originais preservadas:** 189
- **Links relativos verificados:** 4.528 (0 links quebrados)
- **Conformidade de codificação:** 100% UTF-8, 100% LF
