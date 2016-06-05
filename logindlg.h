#ifndef LOGINDLG_H
#define LOGINDLG_H
#include <QDialog>
#include <QObject>

#include "titlewidget.h"
#include "bottomwidget.h"

class QStackedLayout;
class QCheckBox;
class QLineEdit;
class QPushButton;

class loginDlg:public QDialog
{
    Q_OBJECT
public:
    loginDlg(QWidget *parent=0);
    QString getAccount();
    QString getPassword();
    void setErrorLab(QString error);

private slots:
    void showMaxRestored();
    void moveWidget(QPoint point);

signals:
    void sigLogin();
    void sigRegister();

public slots:
    bool eventFilter(QObject *,QEvent *);

protected slots:
    void slotRegister();
    void slotLogin();

private:
    void init();
    void initSlot();

    titleWidget *topWidget;
    QStackedLayout *stackLayout;
    bottomWidget *downWidget;

    QLineEdit *account,*pw;
    QCheckBox *remerberMe,*autoLogin;
    QLabel *remerberLab,*autoLoginLab,*errorLab;
    QToolButton *regietBtn,*findPwBtn;
    QLabel *userImage;
};

#endif // LOGINDLG_H
