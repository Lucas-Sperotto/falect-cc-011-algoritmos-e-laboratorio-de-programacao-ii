# Algoritmos e Laboratório de Programação II (FALECT-CC-011)

**Bacharelado em Ciência da Computação — UNEMAT, Campus de Alto Araguaia**

Repositório de apoio à disciplina, com programas em linguagem C, materiais de aula, atividades, orientações, avaliações e referências. Os exemplos têm finalidade didática e incluem códigos legados que podem exigir análise e correções.

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

### 3. Compilar e executar todos os exemplos

```bash
bash script.sh
```

O script compila separadamente todos os **98 arquivos C** e tenta executar aqueles cuja compilação funciona. Cada programa tem limite padrão de 3 segundos; para usar 5 segundos, rode `bash script.sh 5`. Não combine todos os arquivos na mesma compilação: muitos têm sua própria função `main()`.

**Relatório geral:** `build/execucao_fontes/relatorio.txt`. Para consultar:

```bash
cat build/execucao_fontes/relatorio.txt
```

Para cada exemplo, o diretório `build/execucao_fontes/<grupo>/<nome>/` contém `compilacao.txt`, `saida.txt` e, quando a compilação funciona, o executável `programa`. A pasta `build/` é ignorada pelo Git.

**Atenção:** a execução em lote é **não interativa** (a entrada padrão vem de `/dev/null`); programas que usam `scanf` ou outras entradas poderão terminar com erro, produzir saídas incompletas ou exceder o tempo. Alguns exemplos históricos usam `conio.h`, ausente no GCC Linux. O relatório diferencia erro de compilação, erro de execução e tempo excedido. Executar código C legado pode envolver comportamento indefinido: faça as atividades com supervisão e confira os resultados.

### 4. Compilar e testar um único exemplo

```bash
gcc -std=gnu11 -Wall -Wextra src/Fontes_Aula_1/Prog8.c -lm -o /tmp/prog8
/tmp/prog8
```

Neste modo você poderá digitar entradas no terminal. Substitua o caminho do programa conforme a aula. Para verificar os fontes quanto a codificação UTF-8 e pausas legadas:

```bash
python3 scripts/verificar_fontes_c.py
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

**[Inventário com links individuais para todos os arquivos C](docs/MAPA_FONTES_C.md)**

## Organização do repositório

- `src/`: exemplos em linguagem C distribuídos por aula;
- `aulas/`: roteiros e materiais de aula;
- `atividades/`: atividades e práticas;
- `ead/`: recursos e atividades a distância;
- `exemplos/`: materiais complementares;
- `rubricas/`: critérios de avaliação;
- `templates/`: modelos de documentação e entrega;
- `docs/`: PPC, planos anteriores, mapa dos fontes e orientações;
- `script.sh`: compilação/execução em lote com relatórios;
- `scripts/verificar_fontes_c.py`: inspeção estática de codificação e instruções de pausa.

## Documentação acadêmica

Consulte [Plano da disciplina](PLANO_DISCIPLINA.md), [Cronograma](CRONOGRAMA.md), [Avaliação](AVALIACAO.md), [Política de GitHub](POLITICA_GITHUB.md), [Política de uso de IA](POLITICA_IA.md), [Perguntas frequentes](FAQ.md) e [Revisão dos fontes C](docs/REVISAO_FONTES_C.md).

As entregas e os prazos oficiais devem seguir as orientações informadas pelo professor e pelo SIGAA. O objetivo não é apenas produzir código executável, mas compreender, explicar, testar e justificar os algoritmos.
