# Revisão dos fontes C — codificação, portabilidade e execução

A revisão de 29/10/2026 cobre os **98 fontes** e mantém seus caminhos e nomes. Os cabeçalhos têm ID global, referência para aula Markdown e objetivo. Consulte o [mapa completo](MAPA_FONTES_C.md), o [diagnóstico inicial](auditorias/CODEX_AUDITORIA_INICIAL.md), o [registro das alterações](auditorias/CODEX_IMPLEMENTATION_LOG.md) e os [resultados reais](auditorias/TEST_REPORT.md).

## Codificação e pausas históricas

A inspeção local identificou **17 arquivos CP1252**, convertidos para UTF-8 com português legível. A afirmação da revisão remota anterior de que não havia problemas de codificação não se confirmou nos bytes locais; o [baseline](auditorias/BASELINE_INICIAL.json) preserva esse diagnóstico. Textos alterados usam UTF-8/LF. PDFs originais permanecem intactos.

As chamadas históricas de pausa foram mantidas como comentários, por exemplo:

```c
// system("PAUSE");
```

`gets()` foi substituída por leitura de linha limitada; `conio.h`, `getch()` e `getche()` deram lugar à entrada padrão com confirmação por Enter. Os exemplos de erro intencional preservam a explicação histórica em comentários, com execução limitada ou operação válida identificada.

## Compilação e testes

```bash
bash script.sh
bash script.sh --executar
bash script.sh --executar --sanitizers
python3 scripts/verificar_fontes_c.py
python3 -m unittest discover -s tests -v
```

O primeiro comando somente compila, um executável por fonte, em C11 com advertências habilitadas. A execução usa exclusivamente cenários revisados no [manifesto](../scripts/cenarios_fontes_c.json), com stdin/argumentos definidos, asserções, diretórios temporários, timeout, limites e logs. A versão instrumentada usa ASan e UBSan; o relatório não equipara compilação bem-sucedida à correção do programa.

O verificador estático confere UTF-8, marcadores suspeitos, ausência de pausas ativas, catálogo, IDs e referências. Ele não substitui revisão nem execução. Os testes da infraestrutura verificam timeout, captura de entradas/saídas, isolamento de fixtures, revisão de cenários, compilação sem execução e fronteiras do leitor limitado.

## Limites didáticos preservados

O formato binário de structs é local à ABI; campos de bits e representação por uniões dependem da implementação. Os exemplos POSIX exigem Linux/WSL ou plataforma compatível. A sequência de aulas permanece reconhecível; nenhum conjunto foi convertido em biblioteca ou projeto único.

`scanf` numérico remanescente verifica retorno e limites de domínio, mas pressupõe tokens representáveis nos tipos: endurecer toda a entrada contra números arbitrariamente grandes exigiria outra revisão com `strtol`/`strtof`. Precisão de ponto flutuante e comportamento pseudoaleatório continuam sujeitos às características da plataforma. O relatório de testes explicita os casos efetivamente executados e os limites de cobertura.
