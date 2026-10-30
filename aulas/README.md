# Aulas

Cada aula tem uma página com a **transcrição integral do PDF original**, slide a slide, seguida de explicações complementares, dos programas C relacionados e de exemplos de execução reais. Os PDFs desta pasta são os documentos originais e não foram alterados.

| Aula | Tema | Material original | Fontes em `src/` | Tarefa do SIGAA | Módulo 2026.2 |
|---|---|---|---|---|---|
| [1](aula-01/README.md) | Matrizes (parte 1): vetores e matrizes estáticos | [`Aula_1.pdf`](Aula_1.pdf), 91 slides | `Fontes_Aula_1/` Prog1–Prog12 | [parte 1](../atividades/aula-01-pt1.md) e [parte 2](../atividades/aula-01-pt2.md) | 1 |
| [2](aula-02/README.md) | Matrizes (parte 2): strings | [`Aula_2.pdf`](Aula_2.pdf), 58 slides | `Fontes_Aula_1/` Prog13–Prog25 | [Aula 02](../atividades/aula-02.md) | 1 |
| [3](aula-03/README.md) | Novos tipos de dados com `struct` e `typedef` | [`Aula_3.pdf`](Aula_3.pdf), 79 slides | `Fontes_Aula_3_e_4/` Prog1–Prog5 e BitTest | [Aulas 03 e 04](../atividades/aulas-03-e-04.md) | 1 |
| [4](aula-04/README.md) | Novos tipos de dados com `enum` e `union` | [`Aula_4.pdf`](Aula_4.pdf), 56 slides | `Fontes_Aula_3_e_4/` Prog6–Prog13 | [Aulas 03 e 04](../atividades/aulas-03-e-04.md) | 1 |
| [5](aula-05/README.md) | Ponteiros (parte 1): endereços, indireção e aritmética | [`Aula_5.pdf`](Aula_5.pdf), 74 slides | `Fontes_Aula_5_6_7_e_8/` Prog1–Prog7 | [Aulas 05 e 06](../atividades/aulas-05-e-06.md) | 2 |
| [6](aula-06/README.md) | Ponteiros (parte 2): vetores, strings e vetores de ponteiros | [`Aula_6.pdf`](Aula_6.pdf), 70 slides | `Fontes_Aula_5_6_7_e_8/` Prog8–Prog17 | [Aulas 05 e 06](../atividades/aulas-05-e-06.md) e [Aulas 06 e 07](../atividades/aulas-06-e-07.md) | 2 |
| [7](aula-07/README.md) | Ponteiros (parte 3): funções, `void *`, `qsort` e estruturas | [`Aula_7.pdf`](Aula_7.pdf), 69 slides | `Fontes_Aula_5_6_7_e_8/` Prog18–Prog28 | [Aulas 06 e 07](../atividades/aulas-06-e-07.md) | 2 |
| [8](aula-08/README.md) | Ponteiros (parte 4): alocação dinâmica, lista ligada e linha de comando | [`Aula_8.pdf`](Aula_8.pdf), 66 slides | `Fontes_Aula_5_6_7_e_8/` Prog29–Prog35 | [Aula 08](../atividades/aula-08.md) | 2 |
| [9](aula-09/README.md) | Operadores bit a bit | [`Aula_9.pdf`](Aula_9.pdf), 33 slides | `Fontes_Aula_9/` Prog1–Prog4 | não há tarefa transcrita | 2 |
| [10](aula-10/README.md) | Operações com arquivos (parte 1): fluxos de alto nível | [`Aula_10.pdf`](Aula_10.pdf), 79 slides | `Fontes_Aula_10_e_11/` Prog1–Prog10 | [Aula 10](../atividades/aula-10.md) | 2 |
| [11](aula-11/README.md) | Operações com arquivos (parte 2): registros binários e E/S de baixo nível | [`Aula_11.pdf`](Aula_11.pdf), 107 slides | `Fontes_Aula_10_e_11/` Prog11–Prog20 | [Aula 11](../atividades/aula-11.md) | 2 |

O [plano oficial 2026.2](../PLANO_DISCIPLINA.md) organiza a oferta em três módulos; o terceiro (27/10 a 30/10/2026, prática de programação e algoritmos) não tem material em PDF neste repositório. A numeração histórica de exemplos e PDFs não define novos encontros nem altera o cronograma oficial. Os nomes das pastas de `src/` são históricos: `Fontes_Aula_1` contém também os programas da Aula 2, por exemplo. O [mapa dos 98 programas](../docs/MAPA_FONTES_C.md) relaciona cada fonte à sua aula.

## Como cada página está organizada

Todas as páginas têm as mesmas dez seções:

1. **Identificação da aula** — PDF, programas, tarefa do SIGAA e posição no plano 2026.2.
2. **Objetivos de aprendizagem.**
3. **Conteúdo transcrito** — o texto de cada slide, na ordem original, dentro de blocos de citação. Trechos curtos de código em imagem foram transcritos como texto; capturas de programas inteiros aparecem como figura, com *link* para o fonte. Erros de grafia do original estão marcados com `[sic]`; figuras ilegíveis, em branco ou cortadas estão marcadas como *Lacuna*, sem texto inventado.
4. **Explicações complementares** — aprofundamento dos temas da aula, com diagramas.
5. **Conceitos fundamentais** — tabela de revisão.
6. **Programas C da aula** — finalidade, entradas e saídas, diferenças em relação aos slides e trechos do código revisado.
7. **Exemplos de execução** — saídas reais dos programas, geradas automaticamente.
8. **Observações técnicas** — imprecisões do material, diferenças entre Windows e Linux e pontos de atenção.
9. **Exercícios relacionados** — a tarefa do SIGAA e exercícios propostos.
10. **Referências e fontes consultadas.**

Tudo o que está fora dos blocos de citação da seção 3 foi acrescentado nesta documentação e não faz parte do material original.

## Cobertura da ementa 2026.2

| Item da ementa | Onde é tratado |
|---|---|
| Vetores e matrizes estáticos (inserção, remoção e busca) | Aulas [1](aula-01/README.md) e [2](aula-02/README.md); busca binária na [Aula 7](aula-07/README.md#c-7-8); inserção e remoção em vetor ordenado como [exercício da Aula 1](aula-01/README.md#92-exercícios-propostos-acréscimo-desta-documentação) |
| Ponteiros | Aulas [5](aula-05/README.md), [6](aula-06/README.md), [7](aula-07/README.md) e [8](aula-08/README.md) |
| Variáveis dinâmicas | [Aula 8](aula-08/README.md) |
| Manipulação de arquivos | Aulas [10](aula-10/README.md) e [11](aula-11/README.md) |
| Conceito de estrutura de dados e abstração de dados | Aulas [3](aula-03/README.md) e [4](aula-04/README.md); lista ligada na [Aula 8](aula-08/README.md#c-8-4) |
| Variáveis locais e globais | [Aula 3, seção 4.7](aula-03/README.md#c-3-7) (complemento; o tema não tem slides próprios) |
| Biblioteca STL | Não tratada: a STL pertence à linguagem C++, e todo o material usa C |
| Cadeias de caracteres | Aulas [2](aula-02/README.md) e [6](aula-06/README.md) |
| Registros | Aulas [3](aula-03/README.md) e [4](aula-04/README.md); registros em arquivo na [Aula 11](aula-11/README.md#c-11-1) |
| Programação estruturada | Funções e decomposição em todos os programas; ponteiros para funções na [Aula 7](aula-07/README.md) |
| Passagem por valor e por referência | [Aula 1](aula-01/README.md) (vetores como argumento), [Aula 3](aula-03/README.md) (estruturas) e [Aula 5, seção 4.3](aula-05/README.md#c-5-3) |
| Recursividade | Sem aula própria; complemento na [Aula 7, seção 4.8](aula-07/README.md#c-7-8) |

## Documentos relacionados

- [Matriz de rastreabilidade](../docs/MATRIZ_RASTREABILIDADE.md): para cada slide, a seção da página e o programa C correspondente.
- [Matriz de controle de qualidade (Antigravity)](../docs/auditorias/MATRIZ_RASTREABILIDADE.md): visão por aula, código, exercícios e pendências.
- [Inventário dos PDFs](../docs/INVENTARIO_PDFS.md): os 20 PDFs do repositório, classificados entre aulas, planos e documentos institucionais.
- [Auditoria independente Antigravity](../docs/auditorias/ANTIGRAVITY_AUDIT.md): relatório independente, integração e qualidade dos materiais didáticos.
- [Relatório da documentação das aulas (Claude Code)](../docs/auditorias/CLAUDE_AUDIT.md): método, lacunas encontradas nos PDFs e recomendações para os fontes.
- [Tarefas do SIGAA](../atividades/README.md) e [revisão por fonte](../docs/auditorias/REVISAO_POR_FONTE.md).

## Como manter as páginas

Os trechos de código, os exemplos de execução, as figuras e a matriz são gerados por [`scripts/documentacao_aulas.py`](../scripts/documentacao_aulas.py) a partir dos fontes, dos cenários revisados e dos PDFs; não devem ser editados à mão. Depois de alterar um fonte ou um cenário:

```bash
python3 scripts/documentacao_aulas.py codigo      # trechos de código copiados dos fontes
python3 scripts/documentacao_aulas.py execucoes   # exemplos de execução (compila e executa)
python3 scripts/documentacao_aulas.py figuras     # figuras extraídas dos PDFs
python3 scripts/documentacao_aulas.py matriz      # docs/MATRIZ_RASTREABILIDADE.md
python3 scripts/documentacao_aulas.py validar     # confere tudo; termina com código 1 se houver problema
```

São necessários Python 3, GCC e, para as figuras, a biblioteca PyMuPDF (`pip install pymupdf`).
