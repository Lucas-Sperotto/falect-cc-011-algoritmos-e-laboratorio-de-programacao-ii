#!/usr/bin/env python3
"""Verifica UTF-8 e chamadas de pause ativas em fontes C didáticos."""
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
FILES = sorted((ROOT / "src").rglob("*.c"))
PAUSE = re.compile(r'\bsystem\s*\(\s*["\']pause["\']\s*\)\s*;', re.I)
SUSPECT = re.compile(r'\ufffd|Ã.|Â.|[\u0080-\u009f]')
errors = 0
warnings = 0

for path in FILES:
    try:
        content = path.read_text(encoding="utf-8")
    except UnicodeError as exc:
        print(f"ERRO UTF-8 {path.relative_to(ROOT)}: {exc}")
        errors += 1
        continue
    for number, line in enumerate(content.splitlines(), 1):
        # Ignora linhas inteiramente comentadas; aceita // system("PAUSE");
        stripped = line.lstrip()
        if not stripped.startswith("//") and PAUSE.search(line.split("//", 1)[0]):
            print(f"ERRO pausa ativa {path.relative_to(ROOT)}:{number}: {line.strip()}")
            errors += 1
        if SUSPECT.search(line):
            print(f"AVISO possível texto corrompido {path.relative_to(ROOT)}:{number}")
            warnings += 1

print(f"Arquivos C: {len(FILES)}; erros: {errors}; avisos: {warnings}")
sys.exit(1 if errors else 0)
