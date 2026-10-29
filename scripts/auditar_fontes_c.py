#!/usr/bin/env python3
"""Compila fontes independentes e executa somente cenários revisados do manifesto."""
import argparse
import hashlib
import json
import math
import os
from pathlib import Path
import re
import resource
import signal
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[1]
CATALOG = ROOT / 'docs/auditorias/CATALOGO_FONTES.json'
SCENARIOS = ROOT / 'scripts/cenarios_fontes_c.json'


def limits(seconds, sanitizers):
    """Limites de processo; ASan reserva grande espaço virtual para shadow memory."""
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
    resource.setrlimit(resource.RLIMIT_FSIZE, (2 * 1024 * 1024, 2 * 1024 * 1024))
    cpu = max(1, math.ceil(seconds) + 1)
    resource.setrlimit(resource.RLIMIT_CPU, (cpu, cpu))
    if not sanitizers:
        resource.setrlimit(resource.RLIMIT_AS, (256 * 1024 * 1024, 256 * 1024 * 1024))
    os.umask(0o077)


def run_process(command, cwd, stdin, logdir, seconds, sanitizers=False):
    """Captura saída em arquivos limitados e encerra todo o grupo no timeout."""
    logdir.mkdir(parents=True, exist_ok=True)
    environment = os.environ.copy()
    environment.update(LC_ALL='C.UTF-8', ASAN_OPTIONS='detect_leaks=1:halt_on_error=1',
                       UBSAN_OPTIONS='halt_on_error=1:print_stacktrace=1')
    (logdir / 'entrada.txt').write_text(stdin, encoding='utf-8')
    start = time.monotonic()
    with (logdir / 'stdout.txt').open('wb') as out, (logdir / 'stderr.txt').open('wb') as err:
        process = subprocess.Popen(command, cwd=cwd, stdin=subprocess.PIPE,
                                   stdout=out, stderr=err, env=environment,
                                   start_new_session=True,
                                   preexec_fn=lambda: limits(seconds, sanitizers))
        timed_out = False
        try:
            process.communicate(stdin.encode('utf-8'), timeout=seconds)
        except subprocess.TimeoutExpired:
            timed_out = True
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            process.communicate()
        finally:
            # Também encerra possíveis filhos que tenham sobrevivido ao pai.
            try:
                os.killpg(process.pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
    result = {'command': [str(x) for x in command], 'returncode': process.returncode,
              'timeout': timed_out, 'seconds': round(time.monotonic() - start, 3)}
    (logdir / 'processo.json').write_text(json.dumps(result, ensure_ascii=False, indent=2) + '\n')
    return result


def fixture_path(workdir, relative):
    path = (workdir / relative).resolve()
    if path == workdir.resolve() or not path.is_relative_to(workdir.resolve()):
        raise ValueError(f'Caminho de fixture fora do diretório isolado: {relative}')
    return path


def write_fixtures(workdir, fixtures):
    for relative, content in fixtures.items():
        path = fixture_path(workdir, relative)
        path.parent.mkdir(parents=True, exist_ok=True)
        if isinstance(content, dict):
            path.write_bytes(bytes.fromhex(content['hex']))
        else:
            path.write_text(content, encoding='utf-8')


def validate_cases(catalog, scenarios):
    paths = {row['path'] for row in catalog}
    names = set()
    for case in scenarios:
        key = (case['source'], case['name'])
        if key in names or case['source'] not in paths:
            raise ValueError(f'Cenário duplicado ou fonte desconhecido: {key}')
        if not re.fullmatch(r'[a-z0-9][a-z0-9_-]*', case['name']):
            raise ValueError(f'Nome de cenário inválido: {case["name"]}')
        if case.get('reviewed') is not True:
            raise ValueError(f'Cenário sem revisão: {key}')
        if not any(k in case for k in ('contains', 'stdout', 'stdout_hex', 'files_expected', 'expected_returncode')):
            raise ValueError(f'Cenário sem asserção: {key}')
        for step in case.get('setup', []):
            if step['source'] not in paths:
                raise ValueError(f'Preparação com fonte desconhecido: {step["source"]}')
        names.add(key)


def execute_case(case, binaries, output, seconds, sanitizers):
    case_dir = output / 'execucoes' / Path(case['source']).parent.name / Path(case['source']).stem / case['name']
    case_dir.mkdir(parents=True, exist_ok=True)
    result = {'source': case['source'], 'name': case['name'], 'failures': [],
              'logs': str(case_dir.relative_to(output)), 'setup': []}
    with tempfile.TemporaryDirectory(prefix='dados-', dir=case_dir) as temp:
        workdir = Path(temp)
        write_fixtures(workdir, case.get('files', {}))
        for index, step in enumerate(case.get('setup', [])):
            binary = binaries.get(step['source'])
            if binary is None:
                result['failures'].append('Preparação não compilada: ' + step['source'])
                break
            info = run_process([str(binary), *step.get('args', [])], workdir,
                               step.get('stdin', ''), case_dir / f'setup-{index}', seconds, sanitizers)
            result['setup'].append(info)
            if info['timeout'] or info['returncode'] != step.get('expected_returncode', 0):
                result['failures'].append('Preparação falhou')
                break
        if not result['failures']:
            info = run_process([str(binaries[case['source']]), *case.get('args', [])], workdir,
                               case.get('stdin', ''), case_dir, seconds, sanitizers)
            result.update(info)
            if info['timeout']:
                result['failures'].append('Tempo excedido')
            if info['returncode'] != case.get('expected_returncode', 0):
                result['failures'].append(f'Código esperado {case.get("expected_returncode", 0)}, obtido {info["returncode"]}')
            stdout = (case_dir / 'stdout.txt').read_text(encoding='utf-8', errors='replace')
            stderr = (case_dir / 'stderr.txt').read_text(encoding='utf-8', errors='replace')
            for expected in case.get('contains', []):
                if expected not in stdout:
                    result['failures'].append(f'Saída não contém {expected!r}')
            for forbidden in case.get('not_contains', []):
                if forbidden in stdout:
                    result['failures'].append(f'Saída contém valor proibido {forbidden!r}')
            for expected in case.get('stderr_contains', []):
                if expected not in stderr:
                    result['failures'].append(f'Stderr não contém {expected!r}')
            if 'stdout_hex' in case and (case_dir / 'stdout.txt').read_bytes() != bytes.fromhex(case['stdout_hex']):
                result['failures'].append('Bytes de saída diferentes do esperado')
            if 'stdout' in case and stdout != case['stdout']:
                result['failures'].append('Saída diferente do texto esperado')
            if re.search(r'AddressSanitizer|LeakSanitizer|runtime error:', stderr):
                result['failures'].append('Sanitizador relatou erro')
            artifacts = {}
            for relative, expected in case.get('files_expected', {}).items():
                path = fixture_path(workdir, relative)
                if not path.is_file():
                    result['failures'].append('Arquivo não criado: ' + relative)
                    continue
                raw = path.read_bytes()
                artifacts[relative] = {'bytes': len(raw), 'sha256': hashlib.sha256(raw).hexdigest()}
                if isinstance(expected, str) and raw != expected.encode('utf-8'):
                    result['failures'].append('Conteúdo de arquivo incorreto: ' + relative)
                elif isinstance(expected, dict):
                    if 'hex' in expected and raw != bytes.fromhex(expected['hex']):
                        result['failures'].append('Bytes de arquivo incorretos: ' + relative)
                    if 'same_as' in expected and raw != fixture_path(workdir, expected['same_as']).read_bytes():
                        result['failures'].append('Cópia divergente: ' + relative)
            result['artifacts'] = artifacts
    result['status'] = 'OK' if not result['failures'] else 'FALHOU'
    return result


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--executar', action='store_true', help='Executa apenas os cenários revisados')
    parser.add_argument('--sanitizers', action='store_true', help='Instrumenta com ASan e UBSan')
    parser.add_argument('--timeout', type=float, default=3, help='Segundos por execução (padrão: 3)')
    parser.add_argument('--output', type=Path, help='Diretório de relatórios, dentro de build/')
    parser.add_argument('--source', help='Seleciona caminho exato de um fonte do catálogo')
    parser.add_argument('--case', help='Seleciona nome exato de cenário (pode repetir entre fontes)')
    args = parser.parse_args(argv)
    if not math.isfinite(args.timeout) or args.timeout <= 0 or args.timeout > 60:
        parser.error('--timeout deve ser maior que zero e no máximo 60')
    output = (args.output or ROOT / 'build' / ('auditoria-sanitizers' if args.sanitizers else 'auditoria')).resolve()
    if output == (ROOT / 'build').resolve() or not output.is_relative_to((ROOT / 'build').resolve()):
        parser.error('--output deve ser um subdiretório de build/')
    catalog = json.loads(CATALOG.read_text())
    scenarios = json.loads(SCENARIOS.read_text())
    validate_cases(catalog, scenarios)
    actual = {str(p.relative_to(ROOT)) for p in (ROOT / 'src').rglob('*.c')}
    if actual != {row['path'] for row in catalog}:
        parser.error('Catálogo divergente dos fontes reais')
    selected = [row for row in catalog if not args.source or row['path'] == args.source]
    if not selected:
        parser.error('--source não corresponde a um fonte do catálogo')
    cases = [c for c in scenarios if (not args.source or c['source'] == args.source) and
             (not args.case or c['name'] == args.case)] if args.executar else []
    if args.executar and not cases:
        parser.error('Nenhum cenário corresponde aos filtros')
    # Inclui dependências de preparação mesmo ao selecionar um único fonte.
    needed = {row['path'] for row in selected} | {s['source'] for c in cases for s in c.get('setup', [])}
    output.mkdir(parents=True, exist_ok=True)
    flags = ['-std=c11', '-Wall', '-Wextra', '-Wpedantic', '-O0', '-g']
    if args.sanitizers:
        flags += ['-fsanitize=address,undefined', '-fno-omit-frame-pointer', '-fno-pie', '-no-pie']
    report = {'compiler': subprocess.check_output(['gcc', '--version'], text=True).splitlines()[0],
              'flags': flags, 'execution_requested': args.executar, 'timeout_seconds': args.timeout,
              'sanitizers': args.sanitizers, 'compilation': [], 'cases': [],
              'inputs_sha256': {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest()
                                for p in [Path(__file__), CATALOG, SCENARIOS, *sorted((ROOT / 'src').rglob('*.h'))]}}
    binaries = {}
    for source in sorted(needed):
        logdir = output / 'compilacao' / Path(source).relative_to('src').with_suffix('')
        logdir.mkdir(parents=True, exist_ok=True)
        binary = logdir / 'programa'
        binary.unlink(missing_ok=True)
        command = ['gcc', *flags, str(ROOT / source), '-lm', '-o', str(binary)]
        try:
            completed = subprocess.run(command, capture_output=True, timeout=30)
        except subprocess.TimeoutExpired as exc:
            completed = subprocess.CompletedProcess(command, 124, exc.stdout or b'', exc.stderr or b'')
        diagnostics = completed.stdout + completed.stderr
        (logdir / 'compilacao.txt').write_bytes(diagnostics)
        item = {'source': source, 'sha256': hashlib.sha256((ROOT / source).read_bytes()).hexdigest(),
                'command': command, 'returncode': completed.returncode,
                'warnings': diagnostics.count(b'warning:'), 'log': str((logdir / 'compilacao.txt').relative_to(output))}
        report['compilation'].append(item)
        if completed.returncode == 0:
            binaries[source] = binary
    for case in cases:
        if case['source'] in binaries:
            report['cases'].append(execute_case(case, binaries, output, args.timeout, args.sanitizers))
        else:
            report['cases'].append({'source': case['source'], 'name': case['name'],
                                    'status': 'FALHOU', 'failures': ['Fonte não compilado']})
    report['summary'] = {'sources': len(needed), 'compiled': len(binaries),
                         'compile_failures': len(needed) - len(binaries),
                         'warnings': sum(r['warnings'] for r in report['compilation']),
                         'executed': sum('returncode' in r for r in report['cases']),
                         'passed': sum(r['status'] == 'OK' for r in report['cases']),
                         'failed': sum(r['status'] != 'OK' for r in report['cases'])}
    (output / 'relatorio.json').write_text(json.dumps(report, ensure_ascii=False, indent=2) + '\n')
    lines = [f'{key}={value}' for key, value in report['summary'].items()]
    for case in report['cases']:
        lines.append(f'{case["source"]} [{case["name"]}] => {case["status"]}' +
                     (': ' + '; '.join(case['failures']) if case['failures'] else ''))
    (output / 'relatorio.txt').write_text('\n'.join(lines) + '\n')
    print('\n'.join(lines[:len(report['summary'])]))
    print(f'Relatórios: {output / "relatorio.json"} e {output / "relatorio.txt"}')
    return 1 if report['summary']['compile_failures'] or report['summary']['failed'] else 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (OSError, ValueError, KeyError) as exc:
        print(f'ERRO: {exc}', file=sys.stderr)
        sys.exit(2)
