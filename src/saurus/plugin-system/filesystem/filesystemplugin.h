// For license of this file, see <project-root-folder>/LICENSE.md.

#ifndef FILESYSTEMPLUGIN_H
#define FILESYSTEMPLUGIN_H

#include <QObject>

#include "saurus/plugin-system/pluginbase.h"

class FilesystemPlugin : public QObject, public PluginBase {
  Q_OBJECT

  //Q_PLUGIN_METADATA(IID "com.github.textosaurus.filesystem")

  public:
    explicit FilesystemPlugin(QObject* parent = nullptr);

    virtual QString name() const override;
    virtual QList<BaseSidebar*> sidebars() override;
    virtual QList<QAction*> userActions() override;
};

#endif // FILESYSTEMPLUGIN_H
