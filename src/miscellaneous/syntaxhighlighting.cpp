// For license of this file, see <project-root-folder>/LICENSE.md.

#include "definitions/definitions.h"
#include "miscellaneous/syntaxhighlighting.h"

#include "scintilla/include/SciLexer.h"

#include <QRegularExpression>

SyntaxHighlighting::SyntaxHighlighting(QObject* parent) : QObject(parent), m_fileFilters(QStringList()),
  m_lexers(Lexers()) {}

Lexer SyntaxHighlighting::lexerForFile(const QString& file_name) {
  QRegularExpression reg("(?:\\.)(\\w+$)|($)");
  QString suffix = reg.match(file_name).captured(1);

  return lexerForSuffix(suffix);
}

Lexer SyntaxHighlighting::lexerForSuffix(const QString& suffix) {
  foreach (const Lexer& lex, lexers()) {
    if (lex.m_suffices.contains(suffix)) {
      return lex;
    }
  }

  // We return first lexer, which is lexer for plain text files.
  return m_lexers.first();
}

Lexer SyntaxHighlighting::lexerForName(const QString& name) {
  foreach (const Lexer& lex, lexers()) {
    if (lex.m_name == name) {
      return lex;
    }
  }

  // We return first lexer, which is lexer for plain text files.
  return m_lexers.first();
}

QStringList SyntaxHighlighting::fileFilters() {
  if (m_fileFilters.isEmpty()) {
    foreach (const Lexer& lex, lexers()) {
      m_fileFilters << lex.m_name + tr(" files (*") + lex.m_suffices.join(QL1S(" *")) + QL1C(')');
    }
  }

  return m_fileFilters;
}

Lexers SyntaxHighlighting::lexers() {
  if (m_lexers.isEmpty()) {
    // TODO: dodělat
    m_lexers
      << Lexer(tr("Plain text"), QStringList {
      QSL("txt"), QString()
    }, SCLEX_NULL)
      << Lexer(tr("C++"), QStringList {
      QSL("cpp"), QString()
    }, SCLEX_CPP);

    /*
     #if !defined(WITH_UBUNTU)
       << Lexer(QSL("AVS"), QStringList {
       QSL("avs")
       }, LAMBDA_LEX_GEN(AVS))
     #endif
       << Lexer(QSL("Bash"), QStringList {
       QSL("bash"), QSL("sh"), QSL("zsh")
       }, LAMBDA_LEX_GEN(Bash))
       << Lexer(QSL("Batch"), QStringList {
       QSL("bat"), QSL("cmd")
       }, LAMBDA_LEX_GEN(Batch))
       << Lexer(QSL("CMake"), QStringList {
       QSL("cmake"), QSL("txt")
       }, LAMBDA_LEX_GEN(CMake))
       << Lexer(QSL("CoffeeScript"), QStringList {
       QSL("litcoffee")
       }, LAMBDA_LEX_GEN(CoffeeScript))
       << Lexer(QSL("C++"), QStringList {
       QSL("h"), QSL("hxx"), QSL("hpp"), QSL("c"), QSL("cpp"), QSL("cc"), QSL("cxx")
       }, LAMBDA_LEX_GEN(CPP))
       << Lexer(QSL("C#"), QStringList {
       QSL("cs")
       }, LAMBDA_LEX_GEN(CSharp))
       << Lexer(QSL("D"), QStringList {
       QSL("d")
       }, LAMBDA_LEX_GEN(D))
       << Lexer(QSL("Diff"), QStringList {
       QSL("diff")
       }, LAMBDA_LEX_GEN(Diff))
       << Lexer(QSL("Fortran"), QStringList {
       QSL("for"), QSL("f90"), QSL("f95"), QSL("f2k"), QSL("f23")
       }, LAMBDA_LEX_GEN(Fortran))
       << Lexer(QSL("Fortran77"), QStringList {
       QSL("f77")
       }, LAMBDA_LEX_GEN(Fortran77))
       << Lexer(QSL("HTML"), QStringList {
       QSL("html"), QSL("htm"), QSL("shtml"), QSL("shtm"), QSL("xhtml"), QSL("xht"), QSL("hta")
       }, LAMBDA_LEX_GEN(HTML))
       << Lexer(QSL("IDL"), QStringList {
       QSL("idl")
       }, LAMBDA_LEX_GEN(IDL))
       << Lexer(QSL("Java"), QStringList {
       QSL("java")
       }, LAMBDA_LEX_GEN(Java))
       << Lexer(QSL("JavaScript"), QStringList {
       QSL("js")
       }, LAMBDA_LEX_GEN(JavaScript))
       << Lexer(QSL("JSON"), QStringList {
       QSL("json")
       }, LAMBDA_LEX_GEN(JSON))
       << Lexer(QSL("Lua"), QStringList {
       QSL("lua")
       }, LAMBDA_LEX_GEN(Lua))
       << Lexer(QSL("Make"), QStringList {
       QSL("mak"), QSL("makefile")
       }, LAMBDA_LEX_GEN(Makefile))
       << Lexer(QSL("Markdown"), QStringList {
       QSL("markdown")
       }, LAMBDA_LEX_GEN(Markdown))
       << Lexer(QSL("Matlab"), QStringList {
       QSL("m")
       }, LAMBDA_LEX_GEN(Matlab))
       << Lexer(QSL("Octave"), QStringList {
       QSL("m")
       }, LAMBDA_LEX_GEN(Octave))
       << Lexer(QSL("Pascal"), QStringList {
       QSL("pas"), QSL("pp"), QSL("p"), QSL("inc")
       }, LAMBDA_LEX_GEN(Pascal))
       << Lexer(QSL("Perl"), QStringList {
       QSL("pl"), QSL("pm"), QSL("plx")
       }, LAMBDA_LEX_GEN(Perl))
       << Lexer(QSL("PO"), QStringList {
       QSL("po")
       }, LAMBDA_LEX_GEN(PO))
       << Lexer(QSL("PostScript"), QStringList {
       QSL("ps")
       }, LAMBDA_LEX_GEN(PostScript))
       << Lexer(QSL("POV"), QStringList {
       QSL("pov")
       }, LAMBDA_LEX_GEN(POV))
       << Lexer(QSL("Properties"), QStringList {
       QSL("properties")
       }, LAMBDA_LEX_GEN(Properties))
       << Lexer(QSL("Python"), QStringList {
       QSL("py"), QSL("pyw")
       }, LAMBDA_LEX_GEN(Python))
       << Lexer(QSL("Ruby"), QStringList {
       QSL("rb"), QSL("rbw")
       }, LAMBDA_LEX_GEN(Ruby))
       << Lexer(QSL("Spice"), QStringList {
       QSL("scp"), QSL("out")
       }, LAMBDA_LEX_GEN(Spice))
       << Lexer(QSL("SQL"), QStringList {
       QSL("sql")
       }, LAMBDA_LEX_GEN(SQL))
       << Lexer(QSL("TCL"), QStringList {
       QSL("tcl")
       }, LAMBDA_LEX_GEN(TCL))
       << Lexer(QSL("TeX"), QStringList {
       QSL("tex"), QSL("latex"), QSL("sty"), QSL("cls")
       }, LAMBDA_LEX_GEN(TeX))
       << Lexer(QSL("VeriLog"), QStringList {
       QSL("v"), QSL("sv"), QSL("vh"), QSL("svh")
       }, LAMBDA_LEX_GEN(Verilog))
       << Lexer(QSL("VHDL"), QStringList {
       QSL("vhd"), QSL("vhdl")
       }, LAMBDA_LEX_GEN(VHDL))
       << Lexer(QSL("XML"), QStringList {
       QSL("xml"), QSL("xaml"), QSL("xsl"), QSL("xslt"), QSL("xml"),
       QSL("xsd"), QSL("xul"), QSL("kml"), QSL("svg"), QSL("mxml"), QSL("xsml"),
       QSL("wsdl"), QSL("xlf"), QSL("xliff"), QSL("xbl"), QSL("xml"), QSL("sxbl"),
       QSL("sitemap"), QSL("gml"), QSL("gpx"), QSL("plist"), QSL("ts"), QSL("vcxproj")
       }, LAMBDA_LEX_GEN(XML))
       << Lexer(QSL("YAML"), QStringList {
       QSL("yml"), QSL("yaml")
       }, LAMBDA_LEX_GEN(YAML));*/
  }

  return m_lexers;
}

Lexer SyntaxHighlighting::defaultLexer() {
  return lexers().first();
}

Lexer::Lexer() : m_name(QString()), m_suffices(QStringList()), m_code(SCLEX_NULL) {}

Lexer::Lexer(const QString& name, const QStringList& suffices, int code)
  : m_name(name), m_suffices(suffices), m_code(code) {}

bool Lexer::isEmpty() const {
  return m_name.isEmpty() && m_suffices.isEmpty();
}
