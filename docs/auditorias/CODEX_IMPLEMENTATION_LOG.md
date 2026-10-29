# Registro de implementação

Data da revisão: 29/10/2026, America/Sao_Paulo. Base: `04ac409`. Branch: `codex/auditoria-fontes-c`.

## Resultado e decisões

Os 98 programas foram inventariados, lidos e compilados individualmente. Erros comprovados foram corrigidos, com explicações históricas preservadas. Todos possuem ID estável, objetivo e referência para aula Markdown; os nomes físicos e os agrupamentos foram mantidos. Os 20 PDFs originais permanecem byte a byte idênticos ao baseline.

Não foram criados fontes para os cinco programas ausentes da revisão de 21/09. Não houve acesso autenticado ao SIGAA: foram consultados o PDF oficial 2026.2 e as transcrições locais das atividades. A proposta de migração está registrada sem movimentação no [plano de padronização](PLANO_PADRONIZACAO.md); a correspondência por programa, nome SIGAA e caminho proposto está no [catálogo](CATALOGO_FONTES.json).

## Commits de correção

| Commit | Escopo |
|---|---|
| `51d1c7c` | Inventário de todos os arquivos, diagnóstico e baseline GCC anterior às mudanças |
| `6aa71a2` | Aulas 1/2 e pequena leitura de linha limitada compartilhada |
| `4313d52` | Structs, enumerações, uniões e formatos de saída das aulas 3/4 |
| `57702d1` | Ponteiros, funções, ordenação e alocação das aulas 5–8 |
| `889494e` | Bits e arquivos das aulas 9–11, incluindo APIs POSIX |
| `2a95fd8` | Regressões identificadas na revisão cruzada: CRLF e aritmética com valores finitos grandes |

A infraestrutura de verificação e a documentação dos resultados têm commits próprios posteriores. LF nos textos alterados facilita edições futuras; a conversão dos 17 fontes CP1252 foi feita conscientemente, preservando o português. `.editorconfig` e `.gitattributes` registram a convenção; PDFs são tratados como binários.

## Critérios usados

- **Erro comprovado:** corrigido; problemas e mudanças por fonte em [REVISAO_POR_FONTE.md](REVISAO_POR_FONTE.md).
- **Possível problema:** limites materiais identificados no [relatório de testes](TEST_REPORT.md), incluindo entrada numérica, ABI e falhas de sistema não injetadas.
- **Característica didática intencional:** preservada e explicada. Troca por valor continua sem alterar os argumentos; a comparação de strings por endereço é demonstrada uma vez; linhas que incrementavam vetor ou dereferenciavam void permanecem comentadas, com operações válidas identificadas.
- **Melhoria opcional:** renomear toda a árvore, serializar structs em formato portátil ou substituir sistematicamente scanf por conversores de strings permanece fora desta revisão.

As chamadas históricas `system("PAUSE")` continuam como comentários. Nenhum comando de pausa é executado. `gets` não permanece ativa. As rotinas de baixo nível continuam exemplos POSIX, identificados como tal; PRN foi mantido como referência histórica e o exemplo usa stdout no Linux.

## Revisão das funções efetivamente presentes

[FUNCOES_REVISADAS.json](FUNCOES_REVISADAS.json) registra ocorrências antes/depois por fonte, ignorando comentários, para permitir localizar cada uso de entrada, memória, strings, ordenação e arquivos. As contagens são auxílio de navegação, não prova de correção.

| Família | Verificação e correção |
|---|---|
| gets, scanf/fscanf/sscanf | Linhas limitadas substituem gets; retornos/EOF e larguras de strings conferidos. Conversores com faixa nos registros e operações hexadecimais; limite de scanf numérico restante explicitado. |
| malloc/calloc/free | Falha antes de uso, dimensões positivas e limitadas, liberações em sucesso/erro, limpeza de lista e alocação parcial de matriz. Não houve injeção de falha de malloc. |
| fopen/fclose/fread/fwrite/fseek | Abertura, contagem e retornos, EOF separado de erro, rejeição de registro parcial, seleção do registro correto e fechamento de handles. Layout binário continua local à ABI. |
| qsort | Comparadores por relações, sem subtrair inteiros que podem transbordar; tipos reais dos elementos, extensão correta e preservação da busca com sentinela -1. |
| strcpy/strcat/memcpy/memmove | Capacidade e terminador, sobreposição removida onde a biblioteca a proíbe; cópia didática própria permanece identificada. |
| open/read/write/close | Cabeçalhos POSIX, ssize_t, contagens exatas, EINTR e escritas parciais; busca entre blocos e cópia para mesmo inode sem truncar a origem. |

## Infraestrutura e documentação

`script.sh` delega ao auditor Python. Sem opções, apenas compila; `--executar` seleciona o manifesto revisado. Cada cenário informa entradas, argumentos, resultados esperados e fixtures; binários de structs são gerados pelo escritor revisado no mesmo ambiente. Execuções têm diretório temporário, timeout, limites, stdout/stderr separados e código de saída verificado. O sanitizador roda com detecção de vazamentos, sem reservar teto virtual de 256 MiB incompatível com sua shadow memory.

O auditor grava comandos, hashes de fontes/manifesto/cabeçalho/ferramenta, diagnósticos de compilação, logs por cenário e relatório consolidado JSON/texto. Fixtures com caminhos que escapam do diretório temporário são rejeitadas. Compilação ou cenário malsucedido produz código de saída não zero.

Foram corrigidos os quatro links relativos do plano e três declarações desatualizadas sobre a ausência do PDF 2026.2. O mapa agora tem IDs e links por fonte; a aula 9 recebeu roteiro Markdown. Não se criaram cópias divergentes dos códigos nas aulas. A duplicação histórica de Prog11/12 das aulas 10/11 conserva dois IDs e os dois nomes de entrega.

## Validação e revisão cruzada

Os revisores trabalharam em grupos distintos e depois conferiram códigos de outro grupo e a infraestrutura. Encontraram CRLF no limite do buffer, médias infinitas com somas de floats finitos e preços fora do domínio do exemplo; as correções têm regressões no manifesto/testes. A integração também corrigiu 47 expectativas de diagnóstico que originalmente supunham stdout e stderr unidos: as mensagens passaram a ser verificadas em stderr, mantendo as mesmas asserções.

Os números consolidados, comandos reproduzíveis, perfis, cobertura e limitações estão em [TEST_REPORT.md](TEST_REPORT.md). Resultados versionados preservam os hashes; logs completos permanecem em `build/`, ignorado pelo Git e regenerável. O pull request será disponibilizado para revisão sem merge automático.
