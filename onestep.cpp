
#include "onestep.h"

#include <QMap>
#include <QMessageBox>
#include <QInputDialog>
#include <QTimer>
#include <QDataStream>
#include <QTranslator>
#include <QApplication>
#include <QDebug>
#include <QMetaType>

int OneStep::init(QMap<QString, QString> params, QWidget *parent)
{
    oneStepWindow = new OneStepWindow(parent);
    
    oneStepMenu = new QMenu(parent);
    addOneStepAction = new QAction(oneStepMenu);
    oneStepMenu->addAction(addOneStepAction);
    editOneStepAction = new QAction(oneStepMenu);
    oneStepMenu->addAction(editOneStepAction);
    removeOneStepAction = new QAction(oneStepMenu);
    oneStepMenu->addAction(removeOneStepAction);

    connect(addOneStepAction,&QAction::triggered,this,[&](){
        oneStepWindow->setConfig("","","",22);
        oneStepWindow->show();
    });
    connect(editOneStepAction,&QAction::triggered,this,[&,parent](){
        QStringList stepNameList;
        foreach(OneStepWindow::Config data, oneStepList) {
            stepNameList.append(data.stepName);
        }
        if(stepNameList.isEmpty()) return;
        bool isOk = false;
        QString stepName = QInputDialog::getItem(parent,tr("Edit One Step"),tr("Select a step"),stepNameList,0,false,&isOk);
        if(!isOk || stepName.isEmpty()) return;
        foreach(OneStepWindow::Config data, oneStepList) {
            if(data.stepName == stepName) {
                oneStepWindow->setConfig(data);
                oneStepWindow->show();
                break;
            }
        }
    });
    connect(removeOneStepAction,&QAction::triggered,this,[&,parent](){
        QStringList stepNameList;
        foreach(OneStepWindow::Config data, oneStepList) {
            stepNameList.append(data.stepName);
        }
        if(stepNameList.isEmpty()) return;
        bool isOk = false;
        QString stepName = QInputDialog::getItem(parent,tr("Remove One Step"),tr("Select a step"),stepNameList,0,false,&isOk);
        if(!isOk || stepName.isEmpty()) return;
        foreach(OneStepWindow::Config data, oneStepList) {
            if(data.stepName == stepName) {
                oneStepList.removeOne(data);
                break;
            }
        }
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << oneStepList;
        emit writeSettings("OneStep","oneStepList", QVariant::fromValue(byteArray));
    });

    connect(oneStepWindow,&OneStepWindow::accepted,this,[&,parent](){
        OneStepWindow::Config newData = oneStepWindow->getConfig();
        if(newData.stepName.isEmpty()) {
            QMessageBox::warning(parent,tr("One Step"),tr("Step name can not be empty!"));
            return;
        }
        QString oldStepName = oneStepWindow->getStepInitName();
        if(!oldStepName.isEmpty()) {
            foreach(OneStepWindow::Config data, oneStepList) {
                if(oldStepName == data.stepName) {
                    oneStepList.removeOne(data);
                    break;
                }
            }
        }
        oneStepList.append(newData);
        QByteArray byteArray;
        QDataStream stream(&byteArray, QIODevice::WriteOnly);
        stream << oneStepList;
        emit writeSettings("OneStep","oneStepList", QVariant::fromValue(byteArray));  
    });

    QTimer::singleShot(100,this,[&](){
        QVariant oneStepListVariant;
        emit readSettings("OneStep","oneStepList",oneStepListVariant);
        QByteArray byteArray = oneStepListVariant.toByteArray();
        QDataStream stream(&byteArray, QIODevice::ReadOnly);
        stream >> oneStepList;
    });

    retranslateUi();

    Q_UNUSED(params);
    return 0;
}

QList<QAction *> OneStep::terminalContextAction(QString selectedText, QString workingDirectory, QMenu *parentMenu) {
    QList<QAction *> actionList;
    foreach(OneStepWindow::Config data, oneStepList) {
        QAction *action = new QAction(data.stepName,parentMenu);
        action->setStatusTip(tr("One step to \"%1\"").arg(data.stepName));
        connect(action,&QAction::triggered,this,[=](){
            if(selectedText.isEmpty()) {
                return;
            }
            emit requestSSH2Connect(selectedText,data.userName,data.password,data.port);
        });
        actionList.append(action);
    }
    Q_UNUSED(workingDirectory);
    return actionList;
}

void OneStep::setLanguage(const QLocale &language,QApplication *app) {
    static QTranslator *qtTranslator = nullptr;
    if(qtTranslator == nullptr) {
        qtTranslator = new QTranslator(app);
    } else {
        app->removeTranslator(qtTranslator);
        delete qtTranslator;
        qtTranslator = new QTranslator(app);
    }
    switch(language.language()) {
    case QLocale::Chinese:
        if(qtTranslator->load(":/lang/onestep_zh_CN.qm"))
            app->installTranslator(qtTranslator);
        break;
    default:
    case QLocale::English:
        if(qtTranslator->load(":/lang/onestep_en_US.qm"))
            app->installTranslator(qtTranslator);
        break;
    }
}

void OneStep::retranslateUi() {
    oneStepMenu->setTitle(tr("One Step"));
    addOneStepAction->setText(tr("Add One Step"));
    addOneStepAction->setStatusTip(tr("Add a one step"));
    editOneStepAction->setText(tr("Edit One Step"));
    editOneStepAction->setStatusTip(tr("Edit a one step"));
    removeOneStepAction->setText(tr("Remove One Step"));
    removeOneStepAction->setStatusTip(tr("Remove a one step"));
}

