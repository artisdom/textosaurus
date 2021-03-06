// For license of this file, see <project-root-folder>/LICENSE.md.

#include "saurus/plugin-system/markdown/markdownplugin.h"

#include "definitions/definitions.h"
#include "saurus/miscellaneous/textapplication.h"
#include "saurus/plugin-system/markdown/markdownsidebar.h"

#include <QAction>

MarkdownPlugin::MarkdownPlugin(QObject* parent) : QObject(parent), m_sidebar(nullptr) {}

QString MarkdownPlugin::name() const {
  return QSL("Markdown Preview");
}

QList<BaseSidebar*> MarkdownPlugin::sidebars() {
  return QList<BaseSidebar*>() << sidebar();
}

QList<QAction*> MarkdownPlugin::userActions() {
  return QList<QAction*>({
    sidebar()->m_actionRefreshPreview
  });
}

MarkdownSidebar* MarkdownPlugin::sidebar() {
  if (m_sidebar == nullptr) {
    m_sidebar = new MarkdownSidebar(m_textApp, nullptr);
  }

  return m_sidebar;
}
