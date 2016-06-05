#include "messagelab.h"

messageLab::messageLab(QWidget *parent):QLabel(parent)
{
    timer = new QTimer(this);
    adjustSize();
    //resize(100,30);
    setStyleSheet("background-color: rgba(255, 255, 255, 70%);"
                            " border:1px solid skyblue;  ");
    connect(timer,&QTimer::timeout,[&]() {
        timer->stop();
        close();
    });
    hide();
}


void messageLab::message(QString str)
{
    setText(str);
    resize(100+str.size()*5 ,30);
    timer->start(2000);
    show();
}
