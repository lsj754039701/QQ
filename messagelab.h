#ifndef MESSAGELAB_H
#define MESSAGELAB_H
#include <QLabel>
#include <QTimer>

class messageLab : public QLabel
{
public:
    explicit messageLab(QWidget *parent = 0);
    void message(QString str="");

private:
    QTimer *timer;
};

#endif // MESSAGELAB_H
