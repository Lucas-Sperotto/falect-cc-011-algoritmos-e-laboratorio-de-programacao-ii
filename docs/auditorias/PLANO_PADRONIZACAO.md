# Plano de padronização e compatibilidade

A convenção adotada nesta revisão mantém os caminhos históricos. Identificação global: `A01-P01`, `A03-04-P01`, `A05-08-P01`, `A09-P01`, `A10-11-P01` e `A03-04-BITTEST`. O número é preenchido com dois dígitos apenas no ID; o nome físico e o nome usado no SIGAA são registrados no catálogo.

## Correspondência de diretórios

| Caminho atual preservado | Proposta futura, sem movimentação nesta revisão | Motivo |
|---|---|---|
| `src/Fontes_Aula_1/` | `src/aulas-01-e-02/` | Inclui atividades das aulas 1 e 2 |
| `src/Fontes_Aula_3_e_4/` | `src/aulas-03-e-04/` | Grupo original e BitTest |
| `src/Fontes_Aula_5_6_7_e_8/` | `src/aulas-05-a-08/` | Numeração contínua entre as aulas |
| `src/Fontes_Aula_9/` | `src/aula-09/` | Grupo original |
| `src/Fontes_Aula_10_e_11/` | `src/aulas-10-e-11/` | Grupo original |

A tabela por programa será mantida em `CATALOGO_FONTES.json`: `path` é o caminho atual e adotado; `proposed_path` é somente uma proposta. Não há aprovação implícita de migração posterior. Uma eventual migração deve usar movimentações identificáveis pelo Git, atualizar todos os consumidores e manter um mapa dos nomes SIGAA. Os PDFs originais não serão renomeados nem editados.

## Convenções aplicadas

UTF-8 e LF nos textos alterados; `main(void)` quando não há argumentos; C11; cabeçalho curto com ID, aula Markdown e objetivo original. Preservar os comentários históricos e a progressão. Reutilizar somente uma pequena leitura limitada de linha quando substituir `gets`; manter `scanf` didático com verificações de retorno e limites quando aplicável. Usar `%zu` para `size_t`, `%p` com `void *` para endereços e formatos compatíveis nas demais entradas/saídas.

Compilar cada programa individualmente, sempre com advertências habilitadas. As execuções usam exclusivamente cenários revisados; programas com arquivos recebem cópias temporárias dos dados. Código histórico inválido permanece explicado em comentário, sem execução de comportamento indefinido. Alterações comprovadas e ressalvas didáticas serão discriminadas no registro de implementação.
