#ifndef CLASSIFYFRIEND_H
#define CLASSIFYFRIEND_H

#include <QDialog>

namespace Ui {
class classifyFriend;
}

class classifyFriend : public QDialog
{
    Q_OBJECT

public:
    explicit classifyFriend(QWidget *parent = 0);
    ~classifyFriend();
    QString getGroupName();
    //QString getTestInof();
    //QString getNoteInfo();
    void addGroup(QString name);
    void setFriendID(int friendid);

signals:
    void sigAddFriend(int friendID);

private slots:
    void on_cancleBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::classifyFriend *ui;
    int friendID;
};

#endif // CLASSIFYFRIEND_H
