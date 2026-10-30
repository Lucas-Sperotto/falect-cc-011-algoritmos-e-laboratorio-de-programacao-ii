"""Regressões do gerador e validador da documentação das aulas."""
import importlib.util
from pathlib import Path
import shutil
import unittest

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('documentacao', ROOT / 'scripts/documentacao_aulas.py')
doc = importlib.util.module_from_spec(spec)
spec.loader.exec_module(doc)

FONTE_C = '''#include <stdio.h>
int soma(int, int); /* protótipo: soma( */

/* Soma dois inteiros. */
/* Comentário com chave { que não conta. */
int
soma(int a, int b)
{
    const char *s = "}";
    return a + b + (s[0] == '}');
}

int main(void)
{
    printf("%d\\n", soma(1, 2));
    return 0;
}
'''


class TemporarioNoRepositorio:
    """Diretório descartável dentro de build/, para respeitar caminhos relativos ao repositório."""

    def __enter__(self):
        self.caminho = ROOT / 'build' / 'teste-documentacao' / 'aula-01'
        shutil.rmtree(self.caminho.parent, ignore_errors=True)
        self.caminho.mkdir(parents=True)
        return self.caminho

    def __exit__(self, *erro):
        shutil.rmtree(self.caminho.parent, ignore_errors=True)


class DocumentacaoTests(unittest.TestCase):
    def test_sanitizar_preserva_posicoes(self):
        limpo = doc.sanitizar(FONTE_C)
        self.assertEqual(len(limpo), len(FONTE_C))
        self.assertEqual(limpo.count('\n'), FONTE_C.count('\n'))
        self.assertNotIn('protótipo', limpo)
        self.assertNotIn('"}"', limpo)

    def test_localizar_funcao_ignora_prototipo_e_inclui_comentario(self):
        self.assertEqual(doc.localizar_funcao(FONTE_C, 'soma'), (4, 11))
        self.assertEqual(doc.localizar_funcao(FONTE_C, 'main'), (13, 17))
        with self.assertRaises(doc.ErroDocumentacao):
            doc.localizar_funcao(FONTE_C, 'inexistente')

    def test_localizar_trecho_por_ancoras(self):
        linhas = FONTE_C.splitlines()
        self.assertEqual(doc.localizar_trecho(linhas, 'int main', 'return 0;'), (13, 16))
        self.assertEqual(doc.localizar_trecho(linhas, 'printf'), (15, 15))
        with self.assertRaises(doc.ErroDocumentacao):
            doc.localizar_trecho(linhas, 'int main', 'nunca aparece')

    def test_marcador_de_codigo_e_idempotente_e_detecta_edicao_manual(self):
        with TemporarioNoRepositorio() as pasta:
            md = pasta / 'README.md'
            md.write_text('Antes\n<!-- codigo: src/Fontes_Aula_1/Prog10.c funcao=media -->\n'
                          'conteúdo velho\n<!-- /codigo -->\nDepois\n', encoding='utf-8')
            self.assertTrue(doc.processar_marcadores([md], 'codigo', verificar=True))
            doc.processar_marcadores([md], 'codigo', verificar=False)
            texto = md.read_text(encoding='utf-8')
            self.assertIn('float media(float lista[], int tamanho)', texto)
            self.assertIn('../../../src/Fontes_Aula_1/Prog10.c#L', texto)
            self.assertEqual(doc.processar_marcadores([md], 'codigo', verificar=True), [])
            md.write_text(texto.replace('return m/tamanho;', 'return 0;'), encoding='utf-8')
            self.assertTrue(doc.processar_marcadores([md], 'codigo', verificar=True))

    def test_enderecos_nao_tornam_execucao_divergente(self):
        self.assertEqual(doc.normalizar('px = 0x7ffd1234abcd'), doc.normalizar('px = 0x7ffc00000010'))
        self.assertNotEqual(doc.normalizar('x = 1'), doc.normalizar('x = 2'))

    def test_saida_com_controles_e_bytes_invalidos(self):
        self.assertEqual(doc.texto_visivel(b'\x07a\x1b[0m\n'), '␇a␛[0m\n')
        self.assertIsNone(doc.texto_visivel(b'\xbe\xff'))
        self.assertIn('hexadecimal', doc.bloco_texto('Saída', b'\xbe\xff'))
        self.assertIn('exibidas 2 de 3 linhas', doc.bloco_texto('Saída', b'a\nb\nc\n', maximo=2))
        registro = doc.bloco_texto('Arquivo', b'Ana\x00\x07\x00', hexadecimal=True)
        self.assertIn('(em hexadecimal)', registro)
        self.assertIn('41 6e 61 00 07 00', registro)

    def test_execucao_diverge_do_manifesto(self):
        execucoes = doc.Execucoes()
        try:
            caso = dict(execucoes.cenarios[('src/Fontes_Aula_10_e_11/Prog18.c', 'arquivo-ausente')])
            execucoes.conferir(caso)
            caso['expected_returncode'] = 0
            with self.assertRaises(doc.ErroDocumentacao):
                execucoes.conferir(caso)
        finally:
            execucoes.fechar()

    def test_slug_semelhante_ao_github(self):
        self.assertEqual(doc.slug_github('3.2 Declaração de matrizes (slides 8–11)'),
                         '32-declaração-de-matrizes-slides-811')
        self.assertEqual(doc.slug_github('6. Programas C: `Prog1.c`'), '6-programas-c-prog1c')

    def test_cobertura_de_slides(self):
        with TemporarioNoRepositorio() as pasta:
            readme = pasta / 'README.md'
            readme.write_text('## 3. Conteúdo\n\n### 3.1 Abertura\n\n<a id="slide-1"></a>\n**Slide 1 — Título**\n\n'
                              '> texto A01-P02\n\n<a id="slide-3"></a>\n**Slide 3 — Outro**\n', encoding='utf-8')
            original = dict(doc.PAGINAS)
            try:
                doc.PAGINAS[1] = 3
                registros = doc.coletar_slides(readme)
                self.assertEqual([r['slide'] for r in registros], [1, 3])
                self.assertEqual(registros[0]['ids'], ['A01-P02'])
                self.assertEqual(registros[0]['secao'], '3.1 Abertura')
                self.assertTrue(any('faltam [2]' in p for p in doc.conferir_cobertura(readme)))
            finally:
                doc.PAGINAS.clear()
                doc.PAGINAS.update(original)

    def test_documentacao_do_repositorio_esta_consistente(self):
        self.assertEqual(doc.main(['validar', '--sem-execucao']), 0)


if __name__ == '__main__':
    unittest.main()
