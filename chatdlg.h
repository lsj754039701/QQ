#ifndef CHATDLG_H
#define CHATDLG_H

#include <QDialog>
#include "basedialog.h"
class QDateTime;

namespace Ui {
class chatDlg;
}
QString readFile(QString name);

class chatDlg : public baseDialog
{
    Q_OBJECT

public:
    explicit chatDlg(QString account="", QWidget *parent = 0);
    ~chatDlg();
    void setNick(QString nick);
    void setMeNick(QString nick) {  _nick = nick; }
    void setAccount(QString account="") { _account = account; }
    QString getAccount() { return _account; }
    void addMes(QString mes,QDateTime& time);
    void addHistoryMes( QString mes,QDateTime& time, QString nick="");

protected:
    void createStyleSheet();
    void slotToolBtnClose();

private slots:
    void on_sendBtn_clicked();

    void on_historyBtn_clicked();

signals:
    void sigChatContent(QString account,QString content);
    void sigClose(QString account);
    void sigHistoryChat(QString account,int offset);

private:
    Ui::chatDlg *ui;

    QString _account;
    QString _nick;
    int historyOffset;
};

#endif // CHATDLG_H
