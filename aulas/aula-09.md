# Aula 9 — operações com bits

Material original: [Aula_9.pdf](Aula_9.pdf). Este roteiro vincula os exemplos existentes; não substitui uma atividade oficial do SIGAA, para a qual não há transcrição desta aula no repositório.

| ID estável | Fonte | Objetivo e entrada |
|---|---|---|
| A09-P01 | [Prog1.c](../src/Fontes_Aula_9/Prog1.c) | Complementar bits dos caracteres até `X` ou EOF |
| A09-P02 | [Prog2.c](../src/Fontes_Aula_9/Prog2.c) | Contar os bits de `unsigned int` por deslocamento; sem entrada |
| A09-P03 | [Prog3.c](../src/Fontes_Aula_9/Prog3.c) | Mostrar número hexadecimal em binário; EOF encerra |
| A09-P04 | [Prog4.c](../src/Fontes_Aula_9/Prog4.c) | Calculadora de 16 bits; expressões como `FF00 & A23C`; EOF encerra |

Os fontes usam entrada padrão com confirmação por Enter, substituindo `conio.h`. Largura de `unsigned int` depende da implementação; a calculadora limita seus resultados a 16 bits. Deslocamentos aceitam de 0 a 15. Para complemento use `FFFF ~ 0`, mantendo o formato de três termos do exemplo.

Compile individualmente com `bash script.sh --source src/Fontes_Aula_9/Prog4.c`. Para os cenários revisados, acrescente `--executar` e, opcionalmente, `--sanitizers`. Consulte [a auditoria](../docs/auditorias/CODEX_AUDITORIA_INICIAL.md).
