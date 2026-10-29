# Algoritmos e Laboratório de Programação II (FALECT-CC-011)

**Bacharelado em Ciência da Computação — UNEMAT, Campus de Alto Araguaia**

Repositório de apoio à disciplina, com programas em linguagem C, materiais de aula, atividades, orientações, avaliações e referências. Os exemplos têm finalidade didática e incluem códigos legados que podem exigir análise e correções.

## Oferta 2026.2 — Plano de curso e cronograma

- **Disciplina:** FALECT-CC-011, turma 01, 60h.
- **Módulo 1:** 31/08 a 04/09/2026 — vetores, matrizes, strings e structs.
- **Módulo 2:** 21/09 a 25/09/2026 — ponteiros e manipulação de arquivos.
- **Módulo 3:** 27/10 a 30/10/2026 — prática de programação e algoritmos.
- **Avaliação:** três listas de exercícios de até 10 pontos, com média aritmética simples.

Consulte o [plano de curso 2026.2](PLANO_DISCIPLINA.md), [cronograma](CRONOGRAMA.md) e o [arquivo histórico de planos](docs/planos_old/algoritmos-e-laboratorio-de-programacao-ii/README.md). O [PDF oficial de 2026.2](docs/planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2026.2_01_.pdf) está preservado no histórico.

## Comece por aqui: VS Code + WSL Ubuntu

### 1. Instalação

No Windows, instale **Visual Studio Code**, a extensão **WSL** e o Ubuntu pelo WSL. Abra o terminal Ubuntu e instale os programas de desenvolvimento:

```bash
sudo apt update
sudo apt install -y git build-essential coreutils findutils python3
```

Confira: `git --version`, `gcc --version`, `python3 --version`.

### 2. Clonar o projeto

No terminal Ubuntu (preferencialmente em `~/`, não dentro de `/mnt/c`):

```bash
cd ~
git clone https://github.com/Lucas-Sperotto/falect-cc-011-algoritmos-e-laboratorio-de-programacao-ii.git
cd falect-cc-011-algoritmos-e-laboratorio-de-programacao-ii
code .
```

Abra a pasta no VS Code conectado ao WSL. Para atualizar um clone existente: `git pull --ff-only origin main`.

### 3. Compilar os exemplos

```bash
bash script.sh
```

Compila individualmente os **98 fontes**, com GCC C11, `-Wall -Wextra -Wpedantic`. A execução exige uma opção explícita e usa somente os cenários revisados, com entradas e resultados esperados:

```bash
bash script.sh --executar
bash script.sh --executar --sanitizers
```

Os relatórios ficam em `build/auditoria/relatorio.txt` e `relatorio.json`; os sanitizadores usam `build/auditoria-sanitizers/`. Cada compilação tem log; cada cenário tem `entrada.txt`, `stdout.txt`, `stderr.txt` e metadados do processo. Os arquivos de teste são criados em diretórios temporários e removidos após as verificações. Timeout padrão: 3 segundos por execução; `bash script.sh 5 --executar` usa 5 segundos. Há limites de CPU, memória (exceto reserva virtual dos sanitizadores) e 2 MiB por arquivo de saída.

O [manifesto de cenários](scripts/cenarios_fontes_c.json) contém as entradas, argumentos, fixtures e asserções. Os [resultados efetivamente executados e limitações](docs/auditorias/TEST_REPORT.md) distinguem compilação, execução e correção observada. Alguns exemplos usam APIs POSIX; o ambiente de referência é GCC no Linux/WSL.

### 4. Compilar e testar um único exemplo

```bash
bash script.sh --source src/Fontes_Aula_1/Prog8.c
bash script.sh --source src/Fontes_Aula_1/Prog8.c --executar
```

Para digitar entradas manualmente:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic src/Fontes_Aula_1/Prog8.c -lm -o /tmp/prog8
/tmp/prog8
```

Para verificar UTF-8, pausas históricas comentadas, IDs e referências de aula, e conferir as regressões da infraestrutura:

```bash
python3 scripts/verificar_fontes_c.py
python3 -m unittest discover -s tests -v
```

## Mapa dos códigos

| Aula(s) | Pasta | Arquivos C |
|---|---|---:|
| Aula 1 | [`src/Fontes_Aula_1/`](src/Fontes_Aula_1) | 25 |
| Aulas 10 e 11 | [`src/Fontes_Aula_10_e_11/`](src/Fontes_Aula_10_e_11) | 20 |
| Aulas 3 e 4 | [`src/Fontes_Aula_3_e_4/`](src/Fontes_Aula_3_e_4) | 14 |
| Aulas 5, 6, 7 e 8 | [`src/Fontes_Aula_5_6_7_e_8/`](src/Fontes_Aula_5_6_7_e_8) | 35 |
| Aula 9 | [`src/Fontes_Aula_9/`](src/Fontes_Aula_9) | 4 |
| **Total** | | **98** |

**[Inventário com IDs, aulas e links para os 98 fontes](docs/MAPA_FONTES_C.md)**. Os caminhos históricos foram preservados; consulte o [plano de padronização](docs/auditorias/PLANO_PADRONIZACAO.md).

## Organização do repositório

- `src/`: exemplos em linguagem C distribuídos por aula;
- `aulas/`: roteiros e materiais de aula;
- `atividades/`: atividades e práticas;
- `ead/`: recursos e atividades a distância;
- `exemplos/`: materiais complementares;
- `rubricas/`: critérios de avaliação;
- `templates/`: modelos de documentação e entrega;
- `docs/`: PPC, planos anteriores, mapa dos fontes e orientações;
- `script.sh`: compilação individual e execução opcional dos cenários revisados;
- `scripts/`: auditor de compilação/execução, manifesto de cenários e verificador estático;
- `docs/auditorias/`: inventário inicial, plano de padronização, catálogo e registros da revisão.

## Tarefas individuais do SIGAA

Consulte o [índice das tarefas por aula](atividades/README.md), com enunciados e links para os códigos C correspondentes.

## Documentação acadêmica

Consulte [Plano da disciplina](PLANO_DISCIPLINA.md), [Cronograma](CRONOGRAMA.md), [Avaliação](AVALIACAO.md), [Política de GitHub](POLITICA_GITHUB.md), [Política de uso de IA](POLITICA_IA.md), [Perguntas frequentes](FAQ.md) e [Revisão dos fontes C](docs/REVISAO_FONTES_C.md).

As entregas e os prazos oficiais devem seguir as orientações informadas pelo professor e pelo SIGAA. O objetivo não é apenas produzir código executável, mas compreender, explicar, testar e justificar os algoritmos.
