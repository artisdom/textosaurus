// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef FINDRESULTSMODELITEMEDITOR_H
#define FINDRESULTSMODELITEMEDITOR_H

#include "saurus/gui/sidebars/findresultsmodelitem.h"

#include "saurus/gui/texteditor.h"

#include <QPointer>

class FindResultsModelItemEditor : public FindResultsModelItem {
  Q_OBJECT

  public:
    explicit FindResultsModelItemEditor(TextEditor* editor, QObject* parent = nullptr);

    virtual QVariant data(int role) const override;
    TextEditor* editor() const;

  private:
    QPointer<TextEditor> m_editor;
};

#endif // FINDRESULTSMODELITEMEDITOR_H
