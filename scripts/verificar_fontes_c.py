#!/usr/bin/env python3
"""Confere UTF-8, pausas históricas, identificação e referências dos fontes C."""
from pathlib import Path
import json
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
# Mantém literais para localizar system("PAUSE"), removendo somente comentários.
TOKENS = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
PAUSE = re.compile(r'\bsystem\s*\(\s*"pause"\s*\)', re.I)
SUSPECT = re.compile(r'\ufffd|Ã.|Â.|[\u0080-\u009f]')


def remove_comments(content):
    return TOKENS.sub(lambda m: ' ' if m[0].startswith(('//', '/*')) else m[0], content)


def main():
    files = sorted((ROOT / 'src').rglob('*.c'))
    headers = sorted((ROOT / 'src').rglob('*.h'))
    catalog_path = ROOT / 'docs/auditorias/CATALOGO_FONTES.json'
    catalog = json.loads(catalog_path.read_text())
    by_path = {row['path']: row for row in catalog}
    errors = warnings = 0
    if {str(p.relative_to(ROOT)) for p in files} != set(by_path) or len(by_path) != len(catalog):
        print('ERRO catálogo divergente dos fontes reais ou com caminhos repetidos')
        errors += 1
    if len({row['id'] for row in catalog}) != len(catalog):
        print('ERRO identificações repetidas')
        errors += 1
    for path in files + headers:
        relative = str(path.relative_to(ROOT))
        try:
            content = path.read_text(encoding='utf-8')
        except UnicodeError as exc:
            print(f'ERRO UTF-8 {relative}: {exc}')
            errors += 1
            continue
        if PAUSE.search(remove_comments(content)):
            print(f'ERRO pausa ativa {relative}')
            errors += 1
        for number, line in enumerate(content.splitlines(), 1):
            if SUSPECT.search(line):
                print(f'AVISO possível texto corrompido {relative}:{number}')
                warnings += 1
        if path.suffix == '.c' and relative in by_path:
            row = by_path[relative]
            header = content[:1200]
            doc_relative = Path(__import__('os').path.relpath(ROOT / row['aula_markdown'], path.parent))
            if f'ID: {row["id"]}' not in header or f'Aula: {doc_relative}' not in header:
                print(f'ERRO identificação ou referência ausente {relative}')
                errors += 1
            if not (ROOT / row['aula_markdown']).is_file():
                print(f'ERRO aula Markdown ausente {relative}: {row["aula_markdown"]}')
                errors += 1
    print(f'Arquivos C: {len(files)}; cabeçalhos: {len(headers)}; erros: {errors}; avisos: {warnings}')
    return 1 if errors else 0


if __name__ == '__main__':
    sys.exit(main())
