# Inventário dos PDFs

Levantamento dos 20 arquivos PDF do repositório, feito em 30/10/2026 com PyMuPDF a partir dos arquivos versionados. Nenhum PDF foi alterado; o SHA-256 permite conferir que cada arquivo continua idêntico. A classificação separa o **material de aula**, transcrito integralmente nas [páginas das aulas](../aulas/README.md), dos **documentos oficiais e de referência**, que foram apenas consultados.

| Classe | Quantidade | Tratamento |
|---|---:|---|
| Material de aula (slides) | 11 | transcrição integral, slide a slide, em `aulas/aula-NN/README.md` |
| Planos de curso do SIGAA | 8 | consulta; o plano 2026.2 define a ementa e os módulos usados nas páginas das aulas |
| Projeto pedagógico do curso (PPC) | 1 | consulta institucional; não transcrito |

## Material de aula

Slides do curso *Capacitação em C*, do Prof. Me. Lucas Kriesel Sperotto, convertidos para PDF em 2022. Cada página do PDF é um slide; a numeração dos slides nas páginas das aulas é a numeração das páginas do PDF.

| Arquivo | Páginas | Tamanho | Título da capa (todos com “NÍVEL AVANÇADO”) | Data na capa | Documentação | SHA-256 |
|---|---:|---:|---|---|---|---|
| [`Aula_1.pdf`](../aulas/Aula_1.pdf) | 91 | 1.064 KiB | AULA 1 – MATRIZES – PARTE 1 | 07/10/2022 | [Aula 1](../aulas/aula-01/README.md) | `33b87cfc443cfe9217a271582511acf5c51f43993025a1cf731b1d98a9645b19` |
| [`Aula_2.pdf`](../aulas/Aula_2.pdf) | 58 | 917 KiB | AULA 2 – MATRIZES – PARTE 2 | 07/10/2022 | [Aula 2](../aulas/aula-02/README.md) | `d6f23973d2390413bec3509a688b3190e8f4f367836c8f9a2a1d9c8bfe88db02` |
| [`Aula_3.pdf`](../aulas/Aula_3.pdf) | 79 | 958 KiB | AULA 3 – NOVOS TIPOS DE DADOS COM STRUCT, TYPEDEF, UNION E ENUM - PARTE 1 | 26/09/2022 | [Aula 3](../aulas/aula-03/README.md) | `924d49fcab3bbc81e9feeef7236461a5cd859cdef0625cacaa51aaceb2b49d2e` |
| [`Aula_4.pdf`](../aulas/Aula_4.pdf) | 56 | 921 KiB | AULA 4 – NOVOS TIPOS DE DADOS COM STRUCT, TYPEDEF, UNION E ENUM - PARTE 2 | 07/10/2022 | [Aula 4](../aulas/aula-04/README.md) | `7b3f20792a23e71ad509a6037f85eb9f2e2fb0edaf199bd002748639c156f6a4` |
| [`Aula_5.pdf`](../aulas/Aula_5.pdf) | 74 | 886 KiB | AULA 5 – PONTEIROS - PARTE 1 | 07/10/2022 | [Aula 5](../aulas/aula-05/README.md) | `c3dd7e3a95a56efdc73925fb5540547882ba7cf572d3db1cfbce669508013534` |
| [`Aula_6.pdf`](../aulas/Aula_6.pdf) | 70 | 988 KiB | AULA 6 – PONTEIROS - PARTE 2 | 07/10/2022 | [Aula 6](../aulas/aula-06/README.md) | `72f2f2049e9ba8bde1b7b60581673f6ce6c1b9913fb35de7a27dac9be6d772f3` |
| [`Aula_7.pdf`](../aulas/Aula_7.pdf) | 69 | 1.080 KiB | AULA 7 – PONTEIROS - PARTE 3 | 07/10/2022 | [Aula 7](../aulas/aula-07/README.md) | `e868389bf277d0e9c3618df2c64efc94924b64f3aca19cddb82c1bea6fbd8278` |
| [`Aula_8.pdf`](../aulas/Aula_8.pdf) | 66 | 1.030 KiB | AULA 8 – PONTEIROS - PARTE 4 | 07/10/2022 | [Aula 8](../aulas/aula-08/README.md) | `c391a391f2a8ec728ed0266609e89aa0ee83c8b9e6309487e6f613d824768dc0` |
| [`Aula_9.pdf`](../aulas/Aula_9.pdf) | 33 | 823 KiB | AULA 9 – PONTEIROS AVANÇADOS | 07/10/2022 | [Aula 9](../aulas/aula-09/README.md) | `7626e95bd5310eccec3981662c6171e2d8c5917cfad6f4788091b59fc30b3160` |
| [`Aula_10.pdf`](../aulas/Aula_10.pdf) | 79 | 1.200 KiB | AULA 10 – OPERAÇÕES COM ARQUIVOS – PARTE 1 | 07/10/2022 | [Aula 10](../aulas/aula-10/README.md) | `1c3ebc3deb8c2deedb1c8ce2b469b8b9917a3ab7f199c92d1f4c71d9454b94dc` |
| [`Aula_11.pdf`](../aulas/Aula_11.pdf) | 107 | 1.251 KiB | AULA 11 – OPERAÇÕES COM ARQUIVOS – PARTE 2 | 07/10/2022 | [Aula 11](../aulas/aula-11/README.md) | `f16af0026a0285deb7a3c762f06e8a6800152d15eaf23c7bcee60657a42a94e5` |

Observações:

- A capa da Aula 3 traz o cabeçalho “CAPACITAÇÃO EM LINGUAGEM DE PROGRAMAÇÃO C” e a data 26/09/2022; as demais trazem “ALGORITMO E LABORATÓRIO DE PROGRAMAÇÃO II” e 07/10/2022.
- O título da Aula 9, “Ponteiros avançados”, não corresponde ao conteúdo, que trata de operadores bit a bit ([Aula 9](../aulas/aula-09/README.md)).
- A correspondência entre PDFs, slides, seções e programas C está na [matriz de rastreabilidade](MATRIZ_RASTREABILIDADE.md); as falhas encontradas nos PDFs (figuras em branco ou cortadas, frases incompletas, programas ausentes) estão no [relatório de lacunas](auditorias/CLAUDE_AUDIT.md#lacunas).

## Planos de curso do SIGAA

Planos de curso da disciplina emitidos pelo SIGAA da UNEMAT. O código mudou de AIA105D61 para FALECT-CC-011 a partir de 2024.1. O texto da ementa é o mesmo nos oito planos (comparado sem considerar maiúsculas, acentos e pontuação).

| Arquivo | Semestre | Código e turma | Páginas | Tamanho | Papel nesta documentação | SHA-256 |
|---|---|---|---:|---:|---|---|
| [`Plano_de_Curso_AIA105D61_2021.2_01A_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_AIA105D61_2021.2_01A_.pdf) | 2021.2 | AIA105D61, turma 01A | 2 | 54 KiB | histórico | `0a4e414f7ece677ec8ce42b636374950dc9af32253ba72a40556df7ea83ddc14` |
| [`Plano_de_Curso_AIA105D61_2022.2_01A_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_AIA105D61_2022.2_01A_.pdf) | 2022.2 | AIA105D61, turma 01A | 2 | 53 KiB | histórico | `5889a3aedeed3681dc1f2bb26b53c5886ea053c74747f9351c640448bbd56719` |
| [`Plano_de_Curso_AIA105D61-M_2023.2_01_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_AIA105D61-M_2023.2_01_.pdf) | 2023.2 | AIA105D61-M, turma 01 | 2 | 54 KiB | histórico | `ba465c385a6ab415774639f90125eaafa95c6b904689adf39816f70d3763bae9` |
| [`Plano_de_Curso_FALECT-CC-011_2024.1_01_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2024.1_01_.pdf) | 2024.1 | FALECT-CC-011, turma 01 | 2 | 54 KiB | histórico | `8c3bd8f7afdd2ab8c107d735fbfb02ca988ff3b1d0f104c77371ad05eec8fcd8` |
| [`Plano_de_Curso_FALECT-CC-011_2024.2_01_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2024.2_01_.pdf) | 2024.2 | FALECT-CC-011, turma 01 | 3 | 72 KiB | histórico | `0935782f7200512701776c350cdbd6bfd193ecdcb8fa2909f551df866ab92559` |
| [`Plano_de_Curso_FALECT-CC-011_2025.1_01_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2025.1_01_.pdf) | 2025.1 | FALECT-CC-011, turma 01 | 3 | 72 KiB | histórico | `cf6de665804e643310a3a1a095aa2db8e7794564e1fd10e1f921dd119314364a` |
| [`Plano_de_Curso_FALECT-CC-011_2025.2_01_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2025.2_01_.pdf) | 2025.2 | FALECT-CC-011, turma 01 | 3 | 71 KiB | histórico | `9fd3dd884ebceeb593d6047f6a5116709163e80c193d37cba2ea0b2e81450b5f` |
| [`Plano_de_Curso_FALECT-CC-011_2026.2_01_.pdf`](planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2026.2_01_.pdf) | 2026.2 | FALECT-CC-011, turma 01 | 2 | 53 KiB | **referência da oferta atual**; resumido em [`PLANO_DISCIPLINA.md`](../PLANO_DISCIPLINA.md) | `7708de2466b04fc2276316542ac0323cab2fb1ec18bbd3b67642d157753d0977` |

## Documento institucional

| Arquivo | Páginas | Tamanho | Documento | SHA-256 |
|---|---:|---:|---|---|
| [`ppc_bcc_unemat_aia.pdf`](ppc/ppc_bcc_unemat_aia.pdf) | 177 | 3.808 KiB | Projeto Pedagógico do Curso de Bacharelado em Ciência da Computação, Campus de Alto Araguaia (ano de implantação: 2023) | `3e10732af1e0154cf8d518803dce8a8bffb4cd24c3551ca58e43c54afa6f0fce` |

## Como conferir

```bash
sha256sum aulas/*.pdf docs/planos_old/algoritmos-e-laboratorio-de-programacao-ii/*.pdf docs/ppc/*.pdf
```

A extração das figuras e a verificação das transcrições usam os mesmos arquivos: `python3 scripts/documentacao_aulas.py validar` compara cada figura publicada nas páginas das aulas com os bytes da imagem correspondente no PDF.
