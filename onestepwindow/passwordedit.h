#ifndef PASSWORDEDIT_H
#define PASSWORDEDIT_H

#include <QLineEdit>
#include <QAction>
#include <QIcon>
#include <QtSvg>

class PasswordEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit PasswordEdit(bool show_visibility = true, QWidget *parent = nullptr) 
        : QLineEdit(parent) {
        if (show_visibility) {
            // Add the password hide/shown toggle at the end of the edit box.
            togglepasswordAction = addAction(QIcon(":/icon/onestepwindow/eye.svg"), QLineEdit::TrailingPosition);
            connect(togglepasswordAction, &QAction::triggered, this, &PasswordEdit::on_toggle_password_Action);
        }
        password_shown = false;
        setEchoMode(QLineEdit::Password);
    }

    void setPasswordShown(bool show) {
        if (show) {
            setEchoMode(QLineEdit::Normal);
            password_shown = true;
            togglepasswordAction->setIcon(QIcon(":/icon/onestepwindow/neye.svg"));
        } else {
            setEchoMode(QLineEdit::Password);
            password_shown = false;
            togglepasswordAction->setIcon(QIcon(":/icon/onestepwindow/eye.svg"));
        }
    }

private slots:
    void on_toggle_password_Action() {
        if (!password_shown) {
            setEchoMode(QLineEdit::Normal);
            password_shown = true;
            togglepasswordAction->setIcon(QIcon(":/icon/onestepwindow/neye.svg"));
        } else {
            setEchoMode(QLineEdit::Password);
            password_shown = false;
            togglepasswordAction->setIcon(QIcon(":/icon/onestepwindow/eye.svg"));
        }
    }
    
private:
    QAction *togglepasswordAction;
    bool password_shown;
};
    

#endif // PASSWORDEDIT_H
