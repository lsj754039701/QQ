#ifndef FRIENDTABBAR_H
#define FRIENDTABBAR_H

#include <QWidget>
class friendWidget;

class QVBoxLayout;
namespace Ui {
class friendTabBar;
}

class friendTabBar : public QWidget
{
    Q_OBJECT

public:
    explicit friendTabBar(QString name="",QWidget *parent = 0);
    ~friendTabBar();
    void addFriend(friendWidget *w);
    QString getName();

private slots:
    void on_toolButton_clicked();

signals:
    void sigStartChat(QString account);

private:
    Ui::friendTabBar *ui;
    QVBoxLayout *layout;
    bool curVisable;
    int cntFriends;
};

#endif // FRIENDTABBAR_H
