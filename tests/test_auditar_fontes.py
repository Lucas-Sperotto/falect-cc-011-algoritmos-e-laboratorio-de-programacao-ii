"""Regressões do isolamento, timeout e leitura limitada usados na auditoria."""
import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('auditor', ROOT / 'scripts/auditar_fontes_c.py')
auditor = importlib.util.module_from_spec(spec)
spec.loader.exec_module(auditor)
spec_static = importlib.util.spec_from_file_location('static', ROOT / 'scripts/verificar_fontes_c.py')
static = importlib.util.module_from_spec(spec_static)
spec_static.loader.exec_module(static)


class AuditorTests(unittest.TestCase):
    def test_timeout_and_capture(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            result = auditor.run_process([sys.executable, '-c', 'print("inicio", flush=True); while_flag=True\nwhile while_flag: pass'],
                                         path, '', path / 'log', 0.15)
            self.assertTrue(result['timeout'])
            self.assertNotEqual(result['returncode'], 0)
            self.assertEqual((path / 'log/stdout.txt').read_text(), 'inicio\n')

    def test_stdin_and_exit_code(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            result = auditor.run_process([sys.executable, '-c', 'import sys; print(input()); sys.exit(7)'],
                                         path, 'entrada\n', path / 'log', 2)
            self.assertFalse(result['timeout'])
            self.assertEqual(result['returncode'], 7)
            self.assertEqual((path / 'log/stdout.txt').read_text(), 'entrada\n')

    def test_fixtures_cannot_escape(self):
        with tempfile.TemporaryDirectory() as temp:
            for relative in ('../fora.txt', '/tmp/fora.txt', '.'):
                with self.assertRaises(ValueError):
                    auditor.fixture_path(Path(temp), relative)

    def test_manifest_requires_review_and_unique_case(self):
        catalog = [{'path': 'src/teste.c'}]
        case = {'source': 'src/teste.c', 'name': 'normal', 'expected_returncode': 0}
        with self.assertRaises(ValueError):
            auditor.validate_cases(catalog, [case])
        case['reviewed'] = True
        auditor.validate_cases(catalog, [case])
        with self.assertRaises(ValueError):
            auditor.validate_cases(catalog, [case, case])

    def test_comments_and_historical_pause(self):
        content = '/* system("PAUSE"); */\n// system("pause");\nputs("http://local");'
        self.assertIsNone(static.PAUSE.search(static.remove_comments(content)))
        self.assertIsNotNone(static.PAUSE.search(static.remove_comments(content + '\nsystem("pause");')))

    def test_default_compiles_without_execution(self):
        completed = subprocess.run(['bash', str(ROOT / 'script.sh'), '--source', 'src/Fontes_Aula_3_e_4/Prog3.c',
                                    '--output', str(ROOT / 'build/teste-default')], capture_output=True, text=True)
        self.assertEqual(completed.returncode, 0, completed.stderr)
        report = json.loads((ROOT / 'build/teste-default/relatorio.json').read_text())
        self.assertEqual(report['summary']['executed'], 0)
        self.assertFalse(report['execution_requested'])

    def test_output_file_limit(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            result = auditor.run_process([sys.executable, '-c',
                                          'import sys; sys.stdout.buffer.write(b"x"*(3*1024*1024)); sys.stdout.flush()'],
                                         path, '', path / 'log', 2)
            self.assertNotEqual(result['returncode'], 0)
            self.assertLessEqual((path / 'log/stdout.txt').stat().st_size, 2 * 1024 * 1024)

    def test_memory_limit(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            result = auditor.run_process([sys.executable, '-c', 'buffer=bytearray(300*1024*1024)'],
                                         path, '', path / 'log', 2)
            self.assertNotEqual(result['returncode'], 0)
            self.assertIn('MemoryError', (path / 'log/stderr.txt').read_text())

    def test_catalog_and_scenarios_cover_all_sources(self):
        catalog = json.loads(auditor.CATALOG.read_text())
        cases = json.loads(auditor.SCENARIOS.read_text())
        actual = {str(p.relative_to(ROOT)) for p in (ROOT / 'src').rglob('*.c')}
        self.assertEqual({r['path'] for r in catalog}, actual)
        self.assertEqual({c['source'] for c in cases}, actual)
        auditor.validate_cases(catalog, cases)

    def test_ler_linha_limits_and_recovery(self):
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp)
            code = '#include <stdio.h>\n#include "entrada_segura.h"\nint main(void) { char s[4]; for(int i=0;i<2;i++){ int r=ler_linha(s,sizeof s); printf("%d:%s\\n",r,r?s:""); } }\n'
            (path / 'main.c').write_text(code)
            subprocess.run(['gcc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-I', str(ROOT / 'src'),
                            str(path / 'main.c'), '-o', str(path / 'programa')], check=True)
            for stdin, expected in [('abc\nxy\n', '1:abc\n1:xy\n'),
                                    ('abcd\nxy\n', '0:\n1:xy\n'),
                                    ('abc', '1:abc\n0:\n'), ('', '0:\n0:\n'),
                                    ('a\r\nb\n', '1:a\n1:b\n'),
                                    ('ab\r\nxy\r\n', '1:ab\n1:xy\n'),
                                    ('abc\r\nxy\r\n', '1:abc\n1:xy\n')]:
                result = subprocess.run([str(path / 'programa')], input=stdin, capture_output=True, text=True)
                self.assertEqual(result.stdout, expected)


if __name__ == '__main__':
    unittest.main()
