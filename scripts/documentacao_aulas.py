#!/usr/bin/env python3
"""Mantém a documentação das aulas sincronizada com os PDFs, os fontes C e execuções reais.

Uso (na raiz do repositório):

  python3 scripts/documentacao_aulas.py figuras     extrai dos PDFs as figuras citadas nos README das aulas
  python3 scripts/documentacao_aulas.py codigo      regenera os blocos de código copiados dos fontes C
  python3 scripts/documentacao_aulas.py execucoes   regenera as saídas a partir dos cenários revisados
  python3 scripts/documentacao_aulas.py matriz      regenera docs/MATRIZ_RASTREABILIDADE.md
  python3 scripts/documentacao_aulas.py validar     confere tudo, sem alterar arquivos

Os subcomandos de geração aceitam --verificar: nada é escrito e o código de saída é 1 se houver
divergência. A extração e a comparação byte a byte das figuras exigem PyMuPDF (pip install pymupdf);
sem ele, a validação apenas confere se os arquivos citados existem.

Marcadores usados nos Markdown (o conteúdo entre eles é sempre regenerado):

  <!-- codigo: src/Pasta/ProgN.c -->                     arquivo completo
  <!-- codigo: src/Pasta/ProgN.c funcao=media -->        definição de uma função
  <!-- codigo: src/Pasta/ProgN.c de=`texto` ate=`texto` -->  da primeira linha que contém `de`
                                                          até a primeira seguinte que contém `ate`
  <!-- /codigo -->

  <!-- execucao: src/Pasta/ProgN.c cenario=nome [max=40] [arquivos=resumo|hex] -->
  <!-- /execucao -->

  arquivos=resumo mostra só o tamanho dos arquivos preparados e resultantes;
  arquivos=hex mostra-os sempre em hexadecimal (registros binários).
"""
import argparse
import importlib.util
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
AULAS = ROOT / 'aulas'
CATALOGO = ROOT / 'docs/auditorias/CATALOGO_FONTES.json'
CENARIOS = ROOT / 'scripts/cenarios_fontes_c.json'
MATRIZ = ROOT / 'docs/MATRIZ_RASTREABILIDADE.md'
# Número de páginas de cada aulas/Aula_N.pdf; conferido contra o PDF quando há PyMuPDF.
PAGINAS = {1: 91, 2: 58, 3: 79, 4: 56, 5: 74, 6: 70, 7: 69, 8: 66, 9: 33, 10: 79, 11: 107}
FLAGS_GCC = ['-std=c11', '-Wall', '-Wextra', '-Wpedantic', '-O0']
SECOES_OBRIGATORIAS = 10

MARCADOR = re.compile(r'<!-- (codigo|execucao): (\S+)((?:[ \t]+\w+=(?:`[^`]*`|\S+))*)[ \t]*-->\n'
                      r'(.*?)<!-- /\1 -->', re.S)
OPCAO = re.compile(r'(\w+)=(`[^`]*`|\S+)')
FIGURA = re.compile(r'figuras/s(\d{3})-x(\d+)\.(png|jpe?g)')
ANCORA_SLIDE = re.compile(r'<a id="slide-(\d+)"></a>')
TITULO_SLIDE = re.compile(r'^\*\*Slide (\d+) — (.*)\*\*')  # guloso: títulos podem conter \\*
ID_FONTE = re.compile(r'\b(A\d{2}(?:-\d{2})?-(?:P\d{2}|BITTEST))\b')
LINK_MD = re.compile(r'!?\[(?:[^\[\]]|\[[^\[\]]*\])*\]\(([^)\s]+)(?:\s+"[^"]*")?\)')
LINK_HTML = re.compile(r'\b(?:href|src)="([^"]+)"')
ENDERECO = re.compile(r'0x[0-9a-fA-F]{4,}')


class ErroDocumentacao(Exception):
    """Falha de configuração ou de conteúdo que impede gerar a documentação."""


# ---------------------------------------------------------------------------
# Utilidades gerais
# ---------------------------------------------------------------------------

def readmes_das_aulas():
    return sorted(AULAS.glob('aula-[0-9][0-9]/README.md'))


def numero_aula(caminho):
    return int(Path(caminho).parent.name.split('-')[1])


def relativo(destino, origem_md):
    return os.path.relpath(destino, Path(origem_md).parent).replace(os.sep, '/')


def ler_opcoes(texto):
    return {k: (v[1:-1] if v.startswith('`') else v) for k, v in OPCAO.findall(texto)}


def carregar_catalogo():
    return {linha['id']: linha for linha in json.loads(CATALOGO.read_text(encoding='utf-8'))}


def carregar_auditor():
    """Reaproveita isolamento, limites e timeout do auditor dos fontes."""
    spec = importlib.util.spec_from_file_location('auditor_fontes', ROOT / 'scripts/auditar_fontes_c.py')
    modulo = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(modulo)
    return modulo


def abrir_pdf(numero):
    try:
        import fitz  # PyMuPDF
    except ImportError:
        return None
    return fitz.open(AULAS / f'Aula_{numero}.pdf')


# ---------------------------------------------------------------------------
# Trechos de código
# ---------------------------------------------------------------------------

def sanitizar(texto):
    """Troca comentários e literais por espaços, preservando posições e quebras de linha."""
    saida = list(texto)
    i, n = 0, len(texto)

    def apagar(inicio, fim):
        for k in range(inicio, fim):
            if texto[k] != '\n':
                saida[k] = ' '

    while i < n:
        if texto.startswith('//', i):
            fim = texto.find('\n', i)
            fim = n if fim < 0 else fim
        elif texto.startswith('/*', i):
            fim = texto.find('*/', i + 2)
            fim = n if fim < 0 else fim + 2
        elif texto[i] in '"\'':
            fim = i + 1
            while fim < n and texto[fim] not in (texto[i], '\n'):
                fim += 2 if texto[fim] == '\\' else 1
            fim = min(fim + 1, n)
        else:
            i += 1
            continue
        apagar(i, fim)
        i = fim
    return ''.join(saida)


def localizar_funcao(texto, nome):
    """Retorna (linha_inicial, linha_final), 1-based, da definição de `nome` e do comentário colado acima."""
    limpo = sanitizar(texto)
    for ocorrencia in re.finditer(r'\b' + re.escape(nome) + r'\s*\(', limpo):
        if limpo.count('{', 0, ocorrencia.start()) != limpo.count('}', 0, ocorrencia.start()):
            continue  # chamada dentro de outra função
        j, nivel = ocorrencia.end(), 1
        while j < len(limpo) and nivel:
            nivel += {'(': 1, ')': -1}.get(limpo[j], 0)
            j += 1
        k = j
        while k < len(limpo) and limpo[k].isspace():
            k += 1
        if k >= len(limpo) or limpo[k] != '{':
            continue  # protótipo
        nivel = 0
        for fim in range(k, len(limpo)):
            nivel += {'{': 1, '}': -1}.get(limpo[fim], 0)
            if nivel == 0:
                break
        linhas_limpas = limpo.splitlines()
        linhas = texto.splitlines()
        inicio = limpo.count('\n', 0, ocorrencia.start())  # índice 0-based
        while inicio > 0:
            anterior = linhas_limpas[inicio - 1].strip()
            if not anterior or anterior.endswith((';', '}', '{')) or anterior.startswith('#'):
                break
            inicio -= 1  # tipo de retorno em linha separada
        while inicio > 0 and linhas[inicio - 1].strip() and not linhas_limpas[inicio - 1].strip():
            inicio -= 1  # comentário imediatamente acima
        return inicio + 1, limpo.count('\n', 0, fim) + 1
    raise ErroDocumentacao(f'função {nome!r} não encontrada')


def localizar_trecho(linhas, de, ate=None):
    for i, linha in enumerate(linhas):
        if de in linha:
            if ate is None:
                return i + 1, i + 1
            for j in range(i, len(linhas)):
                if ate in linhas[j]:
                    return i + 1, j + 1
            raise ErroDocumentacao(f'fim do trecho {ate!r} não encontrado após {de!r}')
    raise ErroDocumentacao(f'início do trecho {de!r} não encontrado')


def gerar_codigo(markdown, fonte, opcoes):
    caminho = ROOT / fonte
    if not caminho.is_file() or caminho.suffix not in ('.c', '.h'):
        raise ErroDocumentacao(f'fonte inexistente: {fonte}')
    texto = caminho.read_text(encoding='utf-8')
    linhas = texto.splitlines()
    if 'funcao' in opcoes:
        inicio, fim = localizar_funcao(texto, opcoes['funcao'])
    elif 'de' in opcoes:
        inicio, fim = localizar_trecho(linhas, opcoes['de'], opcoes.get('ate'))
    else:
        inicio, fim = 1, len(linhas)
    trecho = '\n'.join(linhas[inicio - 1:fim]) + '\n'
    cerca = '~~~~' if '```' in trecho else '```'
    if (inicio, fim) == (1, len(linhas)):
        escopo = f'arquivo completo, {len(linhas)} linhas'
    else:
        escopo = f'linha {inicio}' if inicio == fim else f'linhas {inicio}–{fim}'
    return (f'<sub>Copiado de [`{fonte}`]({relativo(caminho, markdown)}#L{inicio}-L{fim}) ({escopo}) '
            'por `scripts/documentacao_aulas.py`; não edite este bloco à mão.</sub>\n\n'
            f'{cerca}c\n{trecho}{cerca}\n')


# ---------------------------------------------------------------------------
# Execuções reais
# ---------------------------------------------------------------------------

class Execucoes:
    """Compila sob demanda e executa cenários revisados do manifesto dos fontes."""

    def __init__(self, tempo=3.0):
        self.tempo = tempo
        self.auditor = carregar_auditor()
        self.cenarios = {(c['source'], c['name']): c for c in json.loads(CENARIOS.read_text(encoding='utf-8'))}
        self.temporario = tempfile.TemporaryDirectory(prefix='doc-aulas-')
        self.binarios = {}

    def fechar(self):
        self.temporario.cleanup()

    def binario(self, fonte):
        if fonte not in self.binarios:
            destino = Path(self.temporario.name) / 'bin' / fonte.replace('/', '__')
            destino.parent.mkdir(parents=True, exist_ok=True)
            comando = ['gcc', *FLAGS_GCC, str(ROOT / fonte), '-lm', '-o', str(destino)]
            resultado = subprocess.run(comando, capture_output=True, text=True, timeout=60)
            if resultado.returncode != 0:
                raise ErroDocumentacao(f'falha ao compilar {fonte}:\n{resultado.stderr}')
            self.binarios[fonte] = destino
        return self.binarios[fonte]

    def instalar(self, fonte, dados):
        """Copia o executável para o diretório de dados, para que argv[0] seja ./ProgN."""
        destino = dados / Path(fonte).stem
        if not destino.exists():
            shutil.copy2(self.binario(fonte), destino)
        return './' + destino.name

    def executar(self, fonte, nome):
        caso = self.cenarios.get((fonte, nome))
        if caso is None or caso.get('reviewed') is not True:
            raise ErroDocumentacao(f'cenário revisado inexistente: {fonte} [{nome}]')
        with tempfile.TemporaryDirectory(dir=self.temporario.name) as pasta:
            pasta = Path(pasta)
            dados = pasta / 'dados'
            dados.mkdir()
            self.auditor.write_fixtures(dados, caso.get('files', {}))
            for indice, passo in enumerate(caso.get('setup', [])):
                info = self.auditor.run_process([self.instalar(passo['source'], dados), *passo.get('args', [])],
                                                dados, passo.get('stdin', ''), pasta / f'preparo-{indice}',
                                                self.tempo)
                if info['timeout'] or info['returncode'] != passo.get('expected_returncode', 0):
                    raise ErroDocumentacao(f'preparação falhou: {passo["source"]} para {fonte} [{nome}]')
            info = self.auditor.run_process([self.instalar(fonte, dados), *caso.get('args', [])], dados,
                                            caso.get('stdin', ''), pasta / 'registro', self.tempo)
            saida = (pasta / 'registro/stdout.txt').read_bytes()
            erro = (pasta / 'registro/stderr.txt').read_bytes()
            gerados = {}
            for relativo_arquivo in sorted(caso.get('files_expected', {})):
                arquivo = self.auditor.fixture_path(dados, relativo_arquivo)
                if arquivo.is_file():
                    gerados[relativo_arquivo] = arquivo.read_bytes()
        if info['timeout']:
            raise ErroDocumentacao(f'tempo excedido: {fonte} [{nome}]')
        self.conferir(caso)
        return caso, info['returncode'], saida, erro, gerados

    def conferir(self, caso):
        """Repete o cenário com o próprio auditor e exige que as asserções do manifesto passem."""
        fontes = {caso['source'], *(passo['source'] for passo in caso.get('setup', []))}
        binarios = {fonte: self.binario(fonte) for fonte in fontes}
        with tempfile.TemporaryDirectory(dir=self.temporario.name) as pasta:
            resultado = self.auditor.execute_case(caso, binarios, Path(pasta), self.tempo, False)
        if resultado['failures']:
            raise ErroDocumentacao(f'cenário {caso["source"]} [{caso["name"]}] diverge do manifesto: '
                                   + '; '.join(resultado['failures']))


def caractere_visivel(c):
    if ord(c) < 32 and c not in '\n\t':
        return chr(0x2400 + ord(c))  # símbolos de controle Unicode: ␇, ␛...
    return '\u2421' if ord(c) == 127 else c


def texto_visivel(dados):
    """Decodifica UTF-8 e torna visíveis os caracteres de controle; None se não for UTF-8."""
    try:
        texto = dados.decode('utf-8')
    except UnicodeDecodeError:
        return None
    return ''.join(caractere_visivel(c) for c in texto)


def despejo_hex(dados, largura=16):
    linhas = []
    for deslocamento in range(0, len(dados), largura):
        bloco = dados[deslocamento:deslocamento + largura]
        hexa = ' '.join(f'{b:02x}' for b in bloco)
        ascii_ = ''.join(chr(b) if 32 <= b < 127 else '.' for b in bloco)
        linhas.append(f'{deslocamento:08x}  {hexa:<{largura * 3 - 1}}  |{ascii_}|')
    return '\n'.join(linhas)


def bloco_texto(rotulo, dados, maximo=None, hexadecimal=False):
    texto = None if hexadecimal else texto_visivel(dados)
    nota = ''
    binario = texto is None
    if binario:
        motivo = 'em hexadecimal' if hexadecimal else 'bytes que não são UTF-8 válido, exibidos em hexadecimal'
        texto, nota = despejo_hex(dados) + '\n', f' ({motivo})'
    if not texto:
        return f'{rotulo}: *(vazia)*\n'
    sem_quebra = not binario and not texto.endswith('\n')
    if maximo:
        linhas = texto.splitlines()
        if len(linhas) > maximo:
            texto = '\n'.join(linhas[:maximo]) + '\n…\n'
            nota += f' (exibidas {maximo} de {len(linhas)} linhas)'
            sem_quebra = False
    if sem_quebra:
        texto += '\n'
        nota += ' (sem quebra de linha final)'
    cerca = '~~~~' if '```' in texto else '```'
    return f'{rotulo}{nota}:\n\n{cerca}text\n{texto}{cerca}\n'


def gerar_execucao(markdown, fonte, opcoes, execucoes):
    nome = opcoes.get('cenario')
    if not nome:
        raise ErroDocumentacao(f'marcador de execução sem cenario= para {fonte}')
    caso, codigo, saida, erro, gerados = execucoes.executar(fonte, nome)
    maximo = int(opcoes['max']) if 'max' in opcoes else None
    comando = ' '.join(['./' + Path(fonte).stem, *caso.get('args', [])])
    partes = [f'Execução real do cenário revisado `{nome}` ([manifesto]({relativo(CENARIOS, markdown)})), '
              f'compilado com `gcc {" ".join(FLAGS_GCC)}`; bloco gerado por `scripts/documentacao_aulas.py`.\n']
    for passo in caso.get('setup', []):
        argumentos = ' '.join(passo.get('args', []))
        partes.append(f'Preparação: executa-se antes `{Path(passo["source"]).stem}` '
                      f'([`{passo["source"]}`]({relativo(ROOT / passo["source"], markdown)}))'
                      + (f' com `{argumentos}`' if argumentos else '') + '.\n')
        if passo.get('stdin'):
            partes.append(bloco_texto('Entrada padrão da preparação', passo['stdin'].encode('utf-8'), maximo))
    modo_arquivos = opcoes.get('arquivos')
    if modo_arquivos not in (None, 'resumo', 'hex'):
        raise ErroDocumentacao(f'arquivos={modo_arquivos} desconhecido (use resumo ou hex)')
    resumir, hexadecimal = modo_arquivos == 'resumo', modo_arquivos == 'hex'
    for arquivo, conteudo in sorted(caso.get('files', {}).items()):
        dados = bytes.fromhex(conteudo['hex']) if isinstance(conteudo, dict) else conteudo.encode('utf-8')
        if resumir:
            partes.append(f'Arquivo preparado `{arquivo}`: {len(dados)} bytes (conteúdo omitido).\n')
        else:
            partes.append(bloco_texto(f'Arquivo preparado `{arquivo}`', dados, maximo, hexadecimal))
    partes.append(f'Comando: `{comando}`\n')
    partes.append(bloco_texto('Entrada padrão', caso.get('stdin', '').encode('utf-8')))
    partes.append(bloco_texto('Saída padrão', saida, maximo))
    if erro:
        partes.append(bloco_texto('Saída de erro', erro, maximo))
    for arquivo, dados in gerados.items():
        if resumir:
            partes.append(f'Arquivo resultante `{arquivo}`: {len(dados)} bytes (conteúdo omitido).\n')
        else:
            partes.append(bloco_texto(f'Arquivo resultante `{arquivo}`', dados, maximo, hexadecimal))
    partes.append(f'Código de saída: `{codigo}`.\n')
    return '\n'.join(partes)


def normalizar(texto):
    return ENDERECO.sub('0x…', texto)


# ---------------------------------------------------------------------------
# Processamento dos marcadores
# ---------------------------------------------------------------------------

def processar_marcadores(arquivos, tipo, verificar, execucoes=None):
    divergencias, atualizados = [], []
    for markdown in arquivos:
        original = markdown.read_text(encoding='utf-8')

        def substituir(m):
            if m.group(1) != tipo:
                return m.group(0)
            opcoes = ler_opcoes(m.group(3))
            try:
                novo = (gerar_codigo(markdown, m.group(2), opcoes) if tipo == 'codigo'
                        else gerar_execucao(markdown, m.group(2), opcoes, execucoes))
            except ErroDocumentacao as exc:
                divergencias.append(f'{markdown.relative_to(ROOT)}: {exc}')
                return m.group(0)
            atual = m.group(4)
            if normalizar(atual) == normalizar(novo):
                return m.group(0)
            if verificar:
                divergencias.append(f'{markdown.relative_to(ROOT)}: bloco {tipo} desatualizado para {m.group(2)} '
                                    f'{m.group(3).strip()}'.rstrip())
            else:
                atualizados.append(markdown)
            return m.group(0)[:m.start(4) - m.start(0)] + novo + f'<!-- /{tipo} -->'

        alterado = MARCADOR.sub(substituir, original)
        if not verificar and alterado != original:
            markdown.write_text(alterado, encoding='utf-8')
    if atualizados:
        print(f'{tipo}: {len(atualizados)} bloco(s) regenerado(s)')
    return divergencias


# ---------------------------------------------------------------------------
# Figuras
# ---------------------------------------------------------------------------

def figuras_citadas(readme):
    texto = readme.read_text(encoding='utf-8')
    return sorted({(int(s), int(x), ext) for s, x, ext in FIGURA.findall(texto)})


def processar_figuras(verificar):
    problemas, avisos = [], []
    for readme in readmes_das_aulas():
        numero = numero_aula(readme)
        pdf = abrir_pdf(numero)
        if pdf is None:
            avisos.append('PyMuPDF indisponível: figuras conferidas apenas quanto à existência')
        for slide, xref, ext in figuras_citadas(readme):
            destino = readme.parent / 'figuras' / f's{slide:03d}-x{xref}.{ext}'
            if pdf is None:
                if not destino.is_file():
                    problemas.append(f'figura ausente: {destino.relative_to(ROOT)}')
                continue
            if not 1 <= slide <= pdf.page_count or xref not in [img[0] for img in pdf[slide - 1].get_images(full=True)]:
                problemas.append(f'{readme.relative_to(ROOT)}: imagem x{xref} não pertence ao slide {slide}')
                continue
            imagem = pdf.extract_image(xref)
            esperado_ext = 'jpeg' if imagem['ext'] in ('jpg', 'jpeg') else imagem['ext']
            if esperado_ext != ('jpeg' if ext in ('jpg', 'jpeg') else ext):
                problemas.append(f'{destino.relative_to(ROOT)}: extensão deveria ser .{esperado_ext}')
                continue
            if destino.is_file() and destino.read_bytes() == imagem['image']:
                continue
            if verificar:
                problemas.append(f'figura ausente ou diferente do PDF: {destino.relative_to(ROOT)}')
            else:
                destino.parent.mkdir(parents=True, exist_ok=True)
                destino.write_bytes(imagem['image'])
        pasta = readme.parent / 'figuras'
        if pasta.is_dir():
            citadas = {f's{s:03d}-x{x}.{e}' for s, x, e in figuras_citadas(readme)}
            for arquivo in sorted(pasta.iterdir()):
                if arquivo.name not in citadas:
                    problemas.append(f'figura não citada no README: {arquivo.relative_to(ROOT)}')
        if pdf is not None and pdf.page_count != PAGINAS[numero]:
            problemas.append(f'Aula_{numero}.pdf tem {pdf.page_count} páginas; esperado {PAGINAS[numero]}')
    return problemas, sorted(set(avisos))


# ---------------------------------------------------------------------------
# Slides e matriz de rastreabilidade
# ---------------------------------------------------------------------------

def coletar_slides(readme):
    """Lê as âncoras de slide e devolve título, seção e programas citados em cada uma."""
    registros, atual, secao = [], None, ''
    for linha in readme.read_text(encoding='utf-8').splitlines():
        if linha.startswith('## '):
            secao = linha[3:].strip()
            if atual:
                registros.append(atual)
                atual = None
            continue
        if linha.startswith('### '):
            secao = linha[4:].strip()
        ancora = ANCORA_SLIDE.search(linha)
        if ancora:
            if atual:
                registros.append(atual)
            atual = {'slide': int(ancora.group(1)), 'titulo': '', 'secao': secao, 'ids': [], 'figuras': 0}
        if atual is None:
            continue
        titulo = TITULO_SLIDE.search(linha)
        if titulo and not atual['titulo'] and int(titulo.group(1)) == atual['slide']:
            atual['titulo'] = titulo.group(2).strip()
        for identificador in ID_FONTE.findall(linha):
            if identificador not in atual['ids']:
                atual['ids'].append(identificador)
        atual['figuras'] += len(FIGURA.findall(linha))
    if atual:
        registros.append(atual)
    return registros


def faixas_de_slides(texto):
    """Converte '3–4, 10–16' em {3, 4, 10, ..., 16}."""
    slides = set()
    for parte in re.split(r',\s*', texto.strip()):
        m = re.fullmatch(r'(\d+)(?:[–-](\d+))?', parte)
        if m:
            slides.update(range(int(m.group(1)), int(m.group(2) or m.group(1)) + 1))
    return slides


def programas_relacionados(readme):
    """Lê a tabela da seção 6 (| [ID](#id) | arquivo | SIGAA | slides | tema |) e devolve slide → IDs."""
    relacao = {}
    padrao = re.compile(r'^\| \[(A\d{2}(?:-\d{2})?-(?:P\d{2}|BITTEST))\]\(#[^)]+\) \|[^|]*\|[^|]*\| ([^|]*) \|', re.M)
    for identificador, faixa in padrao.findall(readme.read_text(encoding='utf-8')):
        for slide in faixas_de_slides(faixa):
            relacao.setdefault(slide, []).append(identificador)
    return relacao


def conferir_cobertura(readme):
    numero = numero_aula(readme)
    slides = [r['slide'] for r in coletar_slides(readme)]
    problemas = []
    esperado = list(range(1, PAGINAS[numero] + 1))
    if sorted(slides) != esperado or len(slides) != len(set(slides)):
        faltam = sorted(set(esperado) - set(slides))
        repetidos = sorted({s for s in slides if slides.count(s) > 1})
        extras = sorted(set(slides) - set(esperado))
        problemas.append(f'{readme.relative_to(ROOT)}: cobertura de slides incorreta; faltam {faltam}, '
                         f'repetidos {repetidos}, inexistentes {extras}')
    if slides != sorted(slides):
        problemas.append(f'{readme.relative_to(ROOT)}: slides fora da ordem do PDF')
    for registro in coletar_slides(readme):
        if not registro['titulo']:
            problemas.append(f'{readme.relative_to(ROOT)}: slide {registro["slide"]} sem linha "**Slide N — título**"')
    return problemas


def celula(texto):
    return texto.replace('|', '\\|')


def gerar_matriz():
    catalogo = carregar_catalogo()
    linhas = ['# Matriz de rastreabilidade: PDF → slide → Markdown → programa C', '',
              '> Arquivo gerado por `python3 scripts/documentacao_aulas.py matriz` a partir das âncoras '
              '`slide-N` dos README das aulas. Não edite à mão: corrija o README da aula e regenere.', '',
              'Cada linha liga uma página do PDF original à seção do Markdown que a transcreve e aos programas C '
              '(IDs estáveis do [catálogo](auditorias/CATALOGO_FONTES.json)). “Programa na figura” indica que o '
              'slide mostra a captura do código; “programa relacionado” indica que o slide explica aquele programa, '
              'conforme a tabela da seção 6 de cada README. Slides sem programa aparecem com “—”.', '',
              '| Aula | PDF | Slides | Transcritos | Slides com programa C | Programas distintos |',
              '|---:|---|---:|---:|---:|---:|']
    tabelas = []
    for readme in readmes_das_aulas():
        numero = numero_aula(readme)
        registros = coletar_slides(readme)
        pdf = f'../aulas/Aula_{numero}.pdf'
        md = relativo(readme, MATRIZ)
        com_programa = [r for r in registros if r['ids']]
        distintos = sorted({i for r in registros for i in r['ids']})
        linhas.append(f'| {numero} | [Aula_{numero}.pdf]({pdf}) | {PAGINAS[numero]} | {len(registros)} | '
                      f'{len(com_programa)} | {len(distintos)} |')
        relacionados = programas_relacionados(readme)
        tabelas += ['', f'## Aula {numero}', '',
                    f'Markdown: [`aulas/aula-{numero:02d}/README.md`]({md}). PDF: [`aulas/Aula_{numero}.pdf`]({pdf}).',
                    '', '| Slide | Título no PDF | Seção do Markdown | Programa na figura | Programa relacionado |',
                    '|---:|---|---|---|---|']

        def lista(ids):
            return ', '.join(f'[{i}]({relativo(ROOT / catalogo[i]["path"], MATRIZ)})' if i in catalogo else i
                             for i in ids) or '—'
        for r in registros:
            outros = [i for i in relacionados.get(r['slide'], []) if i not in r['ids']]
            tabelas.append(f'| [{r["slide"]}]({pdf}#page={r["slide"]}) | {celula(r["titulo"])} | '
                           f'[{celula(r["secao"])}]({md}#slide-{r["slide"]}) | {lista(r["ids"])} | {lista(outros)} |')
    return '\n'.join(linhas + tabelas) + '\n'


def processar_matriz(verificar):
    conteudo = gerar_matriz()
    if MATRIZ.is_file() and MATRIZ.read_text(encoding='utf-8') == conteudo:
        return []
    if verificar:
        return [f'{MATRIZ.relative_to(ROOT)} desatualizada; execute o subcomando matriz']
    MATRIZ.write_text(conteudo, encoding='utf-8')
    return []


# ---------------------------------------------------------------------------
# Links e estrutura
# ---------------------------------------------------------------------------

def slug_github(titulo):
    texto = re.sub(r'!?\[([^\]]*)\]\([^)]*\)', r'\1', titulo)
    texto = re.sub(r'<[^>]+>', '', texto)
    texto = texto.replace('`', '').replace('*', '').strip().lower()
    texto = re.sub(r'[^\w\- ]', '', texto)
    return texto.replace(' ', '-')


def ancoras(markdown):
    texto = markdown.read_text(encoding='utf-8')
    encontradas = set(re.findall(r'<a (?:id|name)="([^"]+)"', texto)) | set(re.findall(r'\bid="([^"]+)"', texto))
    contagem = {}
    em_cerca = False
    for linha in texto.splitlines():
        if linha.lstrip('> ').startswith(('```', '~~~')):
            em_cerca = not em_cerca
            continue
        cabecalho = re.match(r'#{1,6} (.+)', linha)
        if cabecalho and not em_cerca:
            base = slug_github(cabecalho.group(1))
            n = contagem.get(base, 0)
            contagem[base] = n + 1
            encontradas.add(base if n == 0 else f'{base}-{n}')
    return encontradas


def arquivos_markdown():
    ignorar = {'.git', 'build', 'node_modules'}
    return sorted(p for p in ROOT.rglob('*.md') if not ignorar & set(p.relative_to(ROOT).parts))


def conferir_links():
    problemas, cache = [], {}
    for markdown in arquivos_markdown():
        texto = markdown.read_text(encoding='utf-8')
        sem_codigo = re.sub(r'(?ms)^[ >]*(```|~~~).*?^[ >]*\1', '', texto)
        sem_codigo = re.sub(r'`[^`\n]*`', '', sem_codigo)
        alvos = LINK_MD.findall(sem_codigo) + LINK_HTML.findall(sem_codigo)
        for alvo in alvos:
            if re.match(r'[a-z]+:', alvo) or alvo.startswith('//'):
                continue
            caminho, _, fragmento = alvo.partition('#')
            destino = (markdown.parent / caminho).resolve() if caminho else markdown
            origem = markdown.relative_to(ROOT)
            if not destino.exists():
                problemas.append(f'{origem}: link quebrado {alvo}')
                continue
            if not fragmento:
                continue
            if destino.suffix == '.md':
                if destino not in cache:
                    cache[destino] = ancoras(destino)
                if fragmento not in cache[destino]:
                    problemas.append(f'{origem}: âncora inexistente {alvo}')
            elif destino.suffix in ('.c', '.h'):
                linhas = re.fullmatch(r'L(\d+)(?:-L(\d+))?', fragmento)
                total = len(destino.read_text(encoding='utf-8').splitlines())
                if not linhas or not 1 <= int(linhas.group(1)) <= int(linhas.group(2) or linhas.group(1)) <= total:
                    problemas.append(f'{origem}: intervalo de linhas inválido {alvo}')
            elif destino.suffix == '.pdf':
                pagina = re.fullmatch(r'page=(\d+)', fragmento)
                nome = re.fullmatch(r'Aula_(\d+)\.pdf', destino.name)
                if not pagina or (nome and int(pagina.group(1)) > PAGINAS.get(int(nome.group(1)), 0)):
                    problemas.append(f'{origem}: página inválida {alvo}')
    return problemas


def conferir_estrutura():
    problemas = []
    for readme in readmes_das_aulas():
        texto = readme.read_text(encoding='utf-8')
        numeros = [int(n) for n in re.findall(r'^## (\d+)\. ', texto, re.M)]
        if numeros != list(range(1, SECOES_OBRIGATORIAS + 1)):
            problemas.append(f'{readme.relative_to(ROOT)}: seções numeradas {numeros}; esperado 1 a {SECOES_OBRIGATORIAS}')
        if re.search(r'\[FIGURA|\[\[A FAZER\]\]', texto):
            problemas.append(f'{readme.relative_to(ROOT)}: marcação provisória remanescente')
        problemas += conferir_cobertura(readme)
    return problemas


# ---------------------------------------------------------------------------
# Linha de comando
# ---------------------------------------------------------------------------

def markdown_com_marcadores():
    return sorted(AULAS.rglob('*.md'))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest='comando', required=True)
    for nome in ('figuras', 'codigo', 'execucoes', 'matriz'):
        p = sub.add_parser(nome)
        p.add_argument('--verificar', action='store_true', help='apenas compara; não grava arquivos')
    validar = sub.add_parser('validar')
    validar.add_argument('--sem-execucao', action='store_true', help='não compila nem executa os programas')
    args = parser.parse_args(argv)

    problemas, avisos = [], []
    execucoes = None
    try:
        if args.comando in ('figuras', 'validar'):
            p, a = processar_figuras(args.comando == 'validar' or args.verificar)
            problemas += p
            avisos += a
        if args.comando in ('codigo', 'validar'):
            problemas += processar_marcadores(markdown_com_marcadores(), 'codigo',
                                              args.comando == 'validar' or args.verificar)
        if args.comando == 'execucoes' or (args.comando == 'validar' and not args.sem_execucao):
            execucoes = Execucoes()
            problemas += processar_marcadores(markdown_com_marcadores(), 'execucao',
                                              args.comando == 'validar' or args.verificar, execucoes)
        if args.comando in ('matriz', 'validar'):
            problemas += processar_matriz(args.comando == 'validar' or args.verificar)
        if args.comando == 'validar':
            problemas += conferir_estrutura()
            problemas += conferir_links()
    finally:
        if execucoes:
            execucoes.fechar()
    for aviso in avisos:
        print(f'AVISO {aviso}')
    for problema in problemas:
        print(f'ERRO {problema}')
    print(f'{args.comando}: {len(problemas)} problema(s), {len(avisos)} aviso(s)')
    return 1 if problemas else 0


if __name__ == '__main__':
    try:
        sys.exit(main())
    except ErroDocumentacao as exc:
        print(f'ERRO {exc}', file=sys.stderr)
        sys.exit(2)
