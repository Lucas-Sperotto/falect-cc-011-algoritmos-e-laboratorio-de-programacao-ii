# Auditoria inicial dos fontes C

Data: 29/10/2026 (America/Sao_Paulo). Base: `04ac409`. Inspeção anterior às correções.

## Inventário e evidências

Foram inspecionados todos os 160 arquivos versionados: **98 C, 20 PDFs, 38 Markdown, um Bash, um Python**, licença e `.gitignore`. O inventário de caminhos, tamanhos, SHA-256, codificação, duplicações, links e diagnósticos GCC por fonte está em [BASELINE_INICIAL.json](BASELINE_INICIAL.json). O [mapa dos fontes](../MAPA_FONTES_C.md) permite abrir cada programa.

| Grupo histórico | Fontes | Compilam em GCC C11 | Advertências |
|---|---:|---:|---:|
| Aula 1 | 25 | 23 | 25 |
| Aulas 3 e 4 | 14 | 12 | 13 |
| Aulas 5 a 8 | 35 | 27 | 56 |
| Aula 9 | 4 | 3 | 3 |
| Aulas 10 e 11 | 20 | 9 | 3 |
| Total | 98 | 74 | 100 |

Comando por arquivo: `gcc -std=c11 -Wall -Wextra -Wpedantic -O0 <fonte> -lm -o <executável>`. Nenhum programa foi executado nesta fase. Há **24 falhas de compilação**; advertências de arquivos cuja compilação falhou também entram na contagem. Logs brutos locais: `build/auditoria-inicial/completa/`; diagnósticos preservados no JSON versionado.

## Organização acadêmica consultada

O PDF oficial [Plano de Curso 2026.2](../planos_old/algoritmos-e-laboratorio-de-programacao-ii/Plano_de_Curso_FALECT-CC-011_2026.2_01_.pdf) foi lido com PyMuPDF, sem modificar o original. Confirma 60h, três módulos (31/08–04/09; 21–25/09; 27–30/10), C em laboratório e três listas com média aritmética. Horários detalhados excluem 28/10 no terceiro módulo; não reinterpretamos as datas oficiais.

Foram consultadas as dez transcrições de atividades indexadas em [atividades/README.md](../../atividades/README.md). Elas distinguem os nomes SIGAA `Prog01.c` dos nomes reais `Prog1.c`. Não houve acesso autenticado ao SIGAA nem confirmação de prazos ao vivo: a evidência disponível são o PDF oficial e as transcrições locais. A revisão de 21/09 lista cinco programas ausentes, já explicitamente registrados na atividade; não se inventarão fontes correspondentes. Aulas 1/2 compartilham uma pasta; aulas 3/4 e 5–8 também são agrupadas. Aula 9 não possui atividade Markdown própria.

## Diagnóstico documental

- Quatro links quebrados em `PLANO_DISCIPLINA.md`: mapa de fontes, atividades, cronograma e README usam caminhos relativos copiados de outra profundidade.
- README e plano dizem que o PDF de 2026.2 falta, mas ele já está presente.
- **17 fontes não são UTF-8**: três em aulas 3/4, seis em 5–8 e oito em 10/11. CP1252 recupera os comentários em português. A revisão anterior alegava ausência de problemas a partir de leitura remota; essa conclusão não corresponde aos bytes locais.
- Aulas 10/11 `Prog11.c` e `Prog12.c` são cópias byte a byte. Preservar os dois nomes por rastreabilidade das tarefas e documentar a duplicação.
- Numeração reinicia por grupo: `Prog1.c` isolado não é uma identificação global. `BitTest.c` é um exemplo adicional aos 13 programas das aulas 3/4.
- Não foram encontrados `AGENTS.md` aplicáveis. PDFs serão preservados integralmente.

## Classificação técnica

**Erros comprovados:** tipos incompatíveis em `printf`/`scanf`, `typedef` inválido, sintaxe incompleta, `gets`, limites de vetores e strings, leitura de valores não inicializados, divisão por zero, `strcpy` sobreposto, alocação não verificada, vazamentos, acessos após liberação, comparação/subtração de ponteiros sem relação, buscas binárias/textuais fora dos buffers, leitura de registro errado com `fseek`, EOF e resultados de I/O ignorados. Ocorrências e mensagens por caminho estão no baseline; as correções serão detalhadas no registro de implementação.

**Possíveis problemas:** overflow e domínio de entradas numéricas, dependência da ABI em arquivos binários de structs, representação/ordem de bits em uniões, enumerações e pseudoaleatoriedade. Documentar limites e testar os cenários relevantes; compilação não comprova correção.

**Características didáticas intencionais:** troca por valor sem efeito; comparação de strings versus endereços; incremento inválido de nome de vetor; dereferência de `void *`; campos de bits e interpretação de memória. Preservar a explicação histórica em comentários e oferecer operação válida quando necessário. Não modernizar artificialmente a sequência de aulas.

**Melhorias opcionais:** renomear toda a árvore, abstrair cada função repetida, formatar integralmente os fontes ou criar um projeto único. Não são necessárias para corrigir os erros; ficam fora desta intervenção.

## Scripts e plano de execução

`script.sh` compila e executa indiscriminadamente os programas com EOF; não valida saídas, não restringe memória e pode executar práticas intencionalmente inválidas. O verificador Python só detecta codificação e pausa e não cobre os defeitos acima.

1. Versionar inventário e baseline antes das correções.
2. Manter caminhos e nomes; registrar correspondência/IDs estáveis e vincular todos os fontes a aulas Markdown. Criar índice da aula 9.
3. Corrigir fontes por grupo, mantendo pausas históricas comentadas e exemplos explicados. Converter somente arquivos confirmados como CP1252.
4. Tornar compilação o padrão do script. Execução deve exigir opção explícita e cenário revisado, entrada definida, diretório temporário, timeout e limites. Registrar comandos, stderr/stdout, códigos e asserções de saída.
5. Executar GCC e, quando aplicável, ASan/UBSan nos cenários selecionados. Acrescentar regressões dos erros comprovados e consolidar resultados reais.
6. Atualizar documentação, registrar limitações, conferir links e integridade dos PDFs; preparar commits separados e pull request para revisão, sem merge.
