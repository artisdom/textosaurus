// For license of this file, see <project-root-folder>/LICENSE.md.

#include "findresultsmodelitemeditor.h"

#include <QColor>
#include <QVariant>

FindResultsModelItemEditor::FindResultsModelItemEditor(TextEditor* editor, QObject* parent)
  : FindResultsModelItem(parent), m_editor(editor) {}

QVariant FindResultsModelItemEditor::data(int role) const {
  switch (role) {
    case Qt::ItemDataRole::DisplayRole:
      if (m_editor.isNull()) {
        return tr("editor-closed");
      }
      else {
        QString res = tr("%n result(s) - ", "", childCount()) + (m_editor->filePath().isEmpty() ?
                                                                 tr("unnamed-document") :
                                                                 m_editor->filePath());

        return res;
      }

    case Qt::ItemDataRole::BackgroundRole:
      return m_editor.isNull() ? QColor(180, 0, 0, 100) : QColor(0, 180, 0, 100);

    default:
      return QVariant();
  }
}

TextEditor* FindResultsModelItemEditor::editor() const {
  return m_editor.data();
}
