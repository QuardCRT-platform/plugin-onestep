#ifndef ONESTEP_H_
#define ONESTEP_H_

#include "plugininterface.h"
#include "onestepwindow.h"

#define PLUGIN_NAME    "One Step"
#define PLUGIN_VERSION "0.0.1"

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

    QMenu *mainMenu() { return oneStepMenu; }
    QAction *mainAction() { return nullptr; }

    QMenu *terminalContextMenu(QString selectedText, QString workingDirectory, QMenu *parentMenu) {Q_UNUSED(selectedText);Q_UNUSED(workingDirectory);Q_UNUSED(parentMenu); return nullptr;}
    QList<QAction *> terminalContextAction(QString selectedText, QString workingDirectory, QMenu *parentMenu);

private:
    OneStepWindow *oneStepWindow;
    QMenu *oneStepMenu;
    QAction *addOneStepAction;
    QAction *editOneStepAction;
    QAction *removeOneStepAction;
    QList<OneStepWindow::Config> oneStepList;
};

#endif /* ONESTEP_H_ */
