#!/usr/bin/env bash
# Compila individualmente; execução exige --executar e cenários revisados.
# Uso: bash script.sh [segundos] [--executar] [--sanitizers] [opções do auditor]
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
for cmd in gcc python3; do
  if ! command -v "$cmd" >/dev/null 2>&1; then
    echo "Falta $cmd. Instale: sudo apt install -y build-essential python3" >&2
    exit 2
  fi
done
# Compatibilidade: o argumento numérico antigo agora define somente o timeout.
if [[ ${1:-} =~ ^[0-9]+([.][0-9]+)?$ ]]; then
  LIMIT="$1"
  shift
  set -- --timeout "$LIMIT" "$@"
fi
exec python3 "$ROOT/scripts/auditar_fontes_c.py" "$@"
