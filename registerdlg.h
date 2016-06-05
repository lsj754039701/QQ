#ifndef REGISTERDLG_H
#define REGISTERDLG_H

#include <QDialog>
#include "basedialog.h"
#include "client_h/datatype.h"

namespace Ui {
class registerDlg;
}

QString readFile(QString name);

class registerDlg : public baseDialog
{
    Q_OBJECT

public:
    explicit registerDlg(QWidget *parent = 0);
    ~registerDlg();
    bool getState() { return state; }
    registerInfo getRegisterInfo() { return info; }
    void setErrorLab(QString str);

signals:
    void sigRegister();

protected:
    void createStyleSheet();
    void slotToolBtnClose();

private slots:
    void on_registerBtn_clicked();

private:
    Ui::registerDlg *ui;
    bool state;
    registerInfo info;
};

#endif // REGISTERDLG_H
