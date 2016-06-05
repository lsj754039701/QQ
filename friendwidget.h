#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>
#include <client_h/datatype.h>

namespace Ui {
class friendWidget;
}

class friendWidget : public QWidget
{
    Q_OBJECT

public:
    explicit friendWidget(const userInfo& info,QPixmap& pix, QWidget *parent = 0);
    ~friendWidget();
    int getMesTotal();
    void addMes(int num);
    void clearMes();
    QString getAccount() { return _account; }

protected:
        void contextMenuEvent(QContextMenuEvent *e);
        void mouseDoubleClickEvent(QMouseEvent *e);

signals:
        void sigStartChat(QString account);

private:
    Ui::friendWidget *ui;
    QString _account;
};

#endif // FRIENDWIDGET_H
