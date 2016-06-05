#ifndef RECOMMENDWIDGET_H
#define RECOMMENDWIDGET_H

#include <QWidget>
class userInfo;

namespace Ui {
class recommendWidget;
}

class recommendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit recommendWidget(int id, QWidget *parent = 0);
    ~recommendWidget();
    void setUserInfo(QString nick,QString headImage);
    void setUserInfo(userInfo& info);

signals:
    void sigAddFriend(int friendID);
    void sigBtnMes();

private slots:
    void on_addBtn_clicked();

private:
    Ui::recommendWidget *ui;
    int _id;  // friendID
};

#endif // RECOMMENDWIDGET_H
