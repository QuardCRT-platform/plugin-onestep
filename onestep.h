#ifndef ONESTEP_H_
#define ONESTEP_H_

#include "plugininterface.h"
#include "onestepwindow.h"

#define PLUGIN_NAME    "One Step"
#define PLUGIN_VERSION "0.0.3"
#define PLUGIN_WEBSITE "https://github.com/QuardCRT-platform/plugin-onestep"

class OneStep : public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.quardCRT.PluginInterface" FILE "./plugininterface/plugininterface.json")
    Q_INTERFACES(PluginInterface)

public:
    OneStep() {}
    virtual ~OneStep() {}

    int init(QMap<QString, QString> params, QWidget *parent);

    void setLanguage(const QLocale &language,QApplication *app);
    void retranslateUi();
    QString name() { return PLUGIN_NAME; }
    QString version() { return PLUGIN_VERSION; }

    QMap<QString,void *> metaObject() {
        QMap<QString,void *> ret;
        ret.insert("QMenu", (void *)oneStepMenu);
        ret.insert("website", (void *)(&m_website));
        return ret;
    }

    QMenu *terminalContextMenu(QString selectedText, QString workingDirectory, QMenu *parentMenu) {Q_UNUSED(selectedText);Q_UNUSED(workingDirectory);Q_UNUSED(parentMenu); return nullptr;}
    QList<QAction *> terminalContextAction(QString selectedText, QString workingDirectory, QMenu *parentMenu);

private:
    OneStepWindow *oneStepWindow;
    QString m_website = QString(PLUGIN_WEBSITE);
    QMenu *oneStepMenu;
    QAction *addOneStepAction;
    QAction *editOneStepAction;
    QAction *removeOneStepAction;
    QList<OneStepWindow::Config> oneStepList;
};

#endif /* ONESTEP_H_ */
