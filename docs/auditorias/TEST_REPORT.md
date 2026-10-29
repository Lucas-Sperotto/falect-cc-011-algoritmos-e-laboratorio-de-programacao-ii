# Relatório de testes

Execução consolidada em 29/10/2026, America/Sao_Paulo, em Linux com GCC. Os metadados do compilador, comandos, hashes e resultados por cenário estão em [RESULTADOS_TESTES.json](RESULTADOS_TESTES.json). Caminhos absolutos desse artefato foram relativizados ao repositório; os logs originais permanecem em `build/`.

## Resultados observados

| Verificação | Resultado |
|---|---:|
| Baseline anterior às correções | 74/98 compilam; 24 falhas; 100 advertências |
| Compilação final GCC C11 | 98/98; zero advertências |
| Compilação final ASan + UBSan | 98/98; zero advertências |
| Cenários com GCC normal | 277/277 aprovados |
| Mesmos cenários com ASan + UBSan e vazamentos | 277/277 aprovados; nenhum diagnóstico |
| Testes da infraestrutura | 10/10 aprovados |
| UTF-8, pausa, catálogo, IDs e referências | 98 C + 1 cabeçalho; zero erros/avisos |
| PDFs comparados com SHA-256 inicial | 20/20 intactos |

São **554 execuções principais consolidadas**, além das preparações de arquivos binários realizadas pelo próprio escritor revisado. Cada um dos 98 fontes tem ao menos um cenário. Não se somam a esses números as execuções preliminares e a revisão cruzada, que usam alguns casos repetidos.

## Reprodução

Na raiz do repositório:

```bash
bash script.sh
bash script.sh --executar
bash script.sh --executar --sanitizers
python3 scripts/verificar_fontes_c.py
python3 -m unittest discover -s tests -v
```

Sem `--executar`, o auditor não roda os programas. Para um caso específico, use `--source <caminho-exato>` e opcionalmente `--case <nome>`. O [manifesto](../../scripts/cenarios_fontes_c.json) registra entradas, argumentos, fixtures, código esperado, mensagens no canal correto e asserções sobre arquivos. A marca `reviewed` registra revisão; novos cenários devem ser avaliados antes de ativá-la.

Compilação normal: `-std=c11 -Wall -Wextra -Wpedantic -O0 -g`, com `-lm`. O perfil instrumentado acrescenta `-fsanitize=address,undefined -fno-omit-frame-pointer -fno-pie -no-pie`. Não usar PIE estabiliza o mapeamento do ASan no ambiente de execução utilizado. Configuração: `ASAN_OPTIONS=detect_leaks=1:halt_on_error=1` e `UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1`.

Timeout: 3 segundos por execução; limite de CPU derivado do timeout, saída máxima de 2 MiB por arquivo, core dumps desativados. Execuções normais têm teto virtual de 256 MiB. O perfil ASan não usa esse teto virtual, pois sua shadow memory exige reserva maior; dimensões de alocação continuam limitadas nos exemplos. Cada programa que manipula arquivos recebe dados em diretório temporário exclusivo, que é removido após as asserções. Isso é organização de testes, não sandbox de segurança do sistema operacional.

## Cobertura e regressões

- Aulas 1/2: médias, sentinela vazia, 50 valores, dados ausentes/inválidos, calendários, coordenadas do jogo, vitória/empate, histogramas nulos e somas grandes, nomes curtos/exatos/excessivos, strings, cartão e datas.
- Aulas 3/4: structs e uniões, formatos de saída, preços inválidos/não finitos, venda incompleta, 50 vendas, EOF/ESC e limite de mês. Bitfields continuam dependentes da implementação; o resultado binário é observado no GCC usado.
- Aulas 5–8: troca por valor/referência, aritmética de ponteiros no mesmo vetor, nomes, ordenação/busca, argumentos, lista encadeada, validação de dimensões e liberação de memória. Médias com duas entradas finitas `3e38` verificam que não se produz infinito.
- Aulas 9–11: complemento em bytes, hexadecimal com faixa, deslocamentos, abertura de arquivo ausente, EOF, registros parciais, seleção de primeiro/segundo livro, títulos no limite, buffers com NUL e 1024 bytes, busca entre blocos/ausente/maximal, cópia exata e prevenção de truncamento ao copiar para a própria origem.
- Infraestrutura: revisão/duplicação de cenários, catálogo/cobertura, rejeição de fixture fora do diretório, stdin/status, timeout efetivo, teto de saída e de memória, compilação sem execução, comentários de pausa e leitor de linha no limite inclusive CRLF.

Logs por perfil: `build/auditoria/` e `build/auditoria-sanitizers/`. `compilacao/<grupo>/<programa>/compilacao.txt` contém diagnósticos; `execucoes/<grupo>/<programa>/<cenario>/` contém entrada, stdout, stderr, comando, status, duração e logs de preparação. `relatorio.json` e `relatorio.txt` consolidam resultados; falhas de compilação/execução/asserção retornam status não zero no script.

A primeira integração registrou 47 falhas de expectativa por procurar mensagens de stderr em stdout. Os mesmos textos foram movidos para `stderr_contains` e todos os cenários foram reexecutados nos dois perfis. Os números acima correspondem às execuções finais, sem ocultar falhas por desativar casos.

## Limitações

Compilar e passar em cenários finitos não prova correção geral. Permanecem dependência da ABI/padding/endianness nos arquivos binários de structs, representação de uniões e campos de bits, arredondamento de ponto flutuante, comprimentos em bytes e particularidades de terminal/POSIX.

Exemplos que preservam scanf/sscanf numérico exigem tokens representáveis nos tipos; checar retorno não garante análise segura de números arbitrariamente grandes. Não se declarou cobertura de todo esse domínio. Preços do exemplo de vendas das aulas 3/4 têm domínio explícito de 0 a 1 bilhão, peças de 0 a 1 milhão.

Não foram injetadas falhas de malloc, disco cheio, hardware ou todas as interrupções de I/O; os caminhos de retorno foram revisados. Não houve teste exaustivo de calendários nem teste estatístico de rand. Nos ensaios independentes, dimensões máximas de alguns exemplos foram verificadas com captura por pipe, pois sua saída excede 2 MiB; esses ensaios não fazem parte dos 277 cenários padrão. Não houve consulta autenticada ao SIGAA nem confirmação ao vivo de prazos.
