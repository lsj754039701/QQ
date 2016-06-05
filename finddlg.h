#ifndef FINDDLG_H
#define FINDDLG_H

#include <QDialog>
#include "basedialog.h"
#include "recommendwidget.h"
#include "messagelab.h"

namespace Ui {
class findDlg;
}
QString readFile(QString name);

class findDlg : public baseDialog
{
    Q_OBJECT

public:
    explicit findDlg(QWidget *parent = 0);
    ~findDlg();
    void addRecomdWidget(recommendWidget* w);
    void setMesLab(QString mes);
    void clearRecomment();

signals:
    void sigAddFriend(int friendID);
    void sigFindFriend(QString str);

protected:
    void createStyleSheet();
    void slotToolBtnClose();

private slots:
    void on_findPersonBtn_clicked();

private:
    Ui::findDlg *ui;
    QVector<recommendWidget*> vec;
    messageLab *mesLab;
};

#endif // FINDDLG_H
