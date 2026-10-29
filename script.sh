#!/usr/bin/env bash
# Compila cada fonte C e tenta executar com entrada nao interativa.
# Uso: bash script.sh [segundos_por_programa]
set -uo pipefail
ROOT="$(cd "$(dirname "$0")" && pwd)"
SRC="$ROOT/src"
OUT="$ROOT/build/execucao_fontes"
LIMIT="$(printf '%s' "$*" | awk '{print $1}')"
LIMIT="$(test -n "$LIMIT" && echo "$LIMIT" || echo 3)"
if ! [[ "$LIMIT" =~ ^[1-9][0-9]*$ ]]; then
  echo "Informe segundos como inteiro positivo." >&2; exit 2
fi
for cmd in gcc timeout find sort realpath; do
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "Falta $cmd. Instale: sudo apt install -y build-essential coreutils findutils" >&2
    exit 2
  fi
done
test -d "$SRC" || { echo "Pasta src/ nao encontrada."; exit 2; }
mkdir -p "$OUT"
REPORT="$OUT/relatorio.txt"
: > "$REPORT"
total=0; compiled=0; failed=0; ran=0; timeouts=0; runtime_errors=0
log() { printf '%s\n' "$*" | tee -a "$REPORT"; }
log "Relatorio de compilacao e execucao — $(date)"
log "GCC: $(gcc --version | head -n 1)"
log "Limite: $LIMIT segundos por programa; stdin: /dev/null"
log "---------------------------------------------------"
while IFS= read -r -d '' file; do
  ((total+=1))
  relative="$(realpath --relative-to="$SRC" "$file")"
  base="$(basename "$file" .c)"
  group="$(dirname "$relative")"
  dir="$OUT/$group/$base"
  mkdir -p "$dir"
  exe="$dir/programa"
  buildlog="$dir/compilacao.txt"
  runlog="$dir/saida.txt"
  rm -f "$exe"
  : > "$runlog"
  if gcc -std=gnu11 -Wall -Wextra -O0 "$file" -lm -o "$exe" > "$buildlog" 2>&1; then
    ((compiled+=1))
    (
      cd "$dir" || exit 1
      ulimit -f 2048
      timeout --kill-after=1s "$LIMIT" ./programa < /dev/null
    ) > "$runlog" 2>&1
    status=$?
    ((ran+=1))
    if ((status == 0)); then result="OK"
    elif ((status == 124 || status == 137)); then
      result="TIMEOUT ($status)"; ((timeouts+=1))
    else result="ERRO EM EXECUCAO ($status)"; ((runtime_errors+=1))
    fi
  else
    result="ERRO DE COMPILACAO"; ((failed+=1))
  fi
  log "$relative => $result"
  log "  compilacao: $buildlog"
  if [[ -f "$exe" ]]; then log "  saida: $runlog"; fi
done < <(find "$SRC" -type f -name '*.c' -print0 | sort -z)
log "---------------------------------------------------"
log "TOTAL=$total COMPILADOS=$compiled FALHAS_COMPILACAO=$failed"
log "EXECUTADOS=$ran TIMEOUTS=$timeouts FALHAS_EXECUCAO=$runtime_errors"
log "Relatorio geral: $REPORT"
log "Observacao: programas interativos recebem EOF, nao entradas manuais."
