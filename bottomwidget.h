#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H
#include <QWidget>
#include <QObject>

class QPushButton;
class QLabel;

class bottomWidget:public QWidget
{
    Q_OBJECT
public:
    bottomWidget(QWidget *parent=0);

signals:
    void sigLogin();

public slots:
    void slotLogin();

private:
    QLabel *cornerLeft;
    QPushButton *loginBtn;
};

#endif // BOTTOMWIDGET_H
