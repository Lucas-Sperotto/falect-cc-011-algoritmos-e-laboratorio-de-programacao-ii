# Revisão dos fontes C — codificação e portabilidade

## Escopo

A pasta `src/` contém **98 arquivos `.c`** distribuídos em `Fontes_Aula_1`, `Fontes_Aula_3_e_4`, `Fontes_Aula_5_6_7_e_8`, `Fontes_Aula_9` e `Fontes_Aula_10_e_11`.

Esta revisão preserva a lógica dos exemplos didáticos e deixa as chamadas históricas `system("PAUSE");` / `system("pause");` **na mesma linha, mas comentadas**:

```c
// system("PAUSE");
```

O comando é específico do ambiente Windows e não é necessário para a execução no terminal; a instrução comentada não é compilada nem executada.

## Codificação de caracteres

- Padronizar novos textos e comentários como **UTF-8**; configurar o editor para UTF-8 e preferir finais de linha LF em arquivos novos.
- A leitura dos 98 fontes pelo serviço de arquivos do GitHub não identificou os indicadores comuns de texto corrompido (caractere de substituição `�`, sequências `Ã` e `Â` e controles C1).
- Isso **não garante** que toda acentuação original esteja linguisticamente correta; revisar termos e mensagens conforme o contexto.
- Não converter automaticamente strings e comentários apenas por suspeita de codificação: isso pode destruir conteúdo legítimo. O verificador abaixo inspeciona marcadores conhecidos.

## Compilação e execução

Cada exemplo tem sua própria função `main`; **não** compilar todos os fontes em um único executável:

```bash
gcc -std=c11 -Wall -Wextra src/Fontes_Aula_1/Prog8.c -o /tmp/aula-prog8
/tmp/aula-prog8
```

Alguns códigos são exemplos históricos e podem apresentar erros, comportamentos indefinidos ou dependências **não portáveis**, independentemente da remoção da pausa. Em especial, fontes que incluem `<conio.h>` ou usam `getche()` / `getch()` exigem revisão ou ambiente compatível. Não há declaração de que os 98 programas compilaram ou passaram em testes de execução.

## Verificação automatizada

```bash
python3 scripts/verificar_fontes_c.py
```

O script verifica a leitura UTF-8, possíveis artefatos de codificação e chamadas de pausa que ainda estejam ativas. Mensagens de possíveis artefatos devem ser revisadas manualmente. A verificação estática não substitui compilação, testes de execução nem avaliação dos conceitos apresentados.

## Diretriz para futuras edições

1. Preservar a linha original de pausa ao comentá-la; não apagá-la nem substituí-la por outra pausa.
2. Manter os exemplos separados, com suas finalidades didáticas.
3. Fazer correções de acentuação apenas quando o texto original e a correção pretendida forem inequívocos.
4. Validar compilação e comportamento de cada programa alterado quando houver mudanças além de comentários.
