#include "bottomwidget.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QLinearGradient>
#include <QPalette>
#include <QFile>
#include <QDebug>

bottomWidget::bottomWidget(QWidget *parent):QWidget(parent)
{
    QFile qss(":/qss/bottomWidget.css");
    QString css="";
    if (qss.open(QIODevice::ReadOnly)) {
        css=qss.readAll();
    } // qDebug()<<css;
    qss.close();

    cornerLeft=new QLabel;
    loginBtn=new QPushButton;

    cornerLeft->setPixmap(QPixmap(":/login/image/corner_left.png"));
    cornerLeft->setScaledContents(true);
    cornerLeft->setFixedSize(QSize(30,30));

    loginBtn->setText("登陆");
//    loginBtn->setFixedHeight(33);
//    loginBtn->setFixedWidth(100);
    loginBtn->setObjectName("loginBtn");
    loginBtn->setStyleSheet(css);
    loginBtn->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *layout=new QHBoxLayout;
    layout->addWidget(cornerLeft,0,Qt::AlignBottom);
    layout->addStretch();
    layout->addWidget(loginBtn);
    layout->addStretch();
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);
    setFixedHeight(50);

    QPoint top(rect().topRight().x()/2,rect().topRight().y());
    QPoint down(rect().bottomRight().x()/2,rect().bottomRight().y());
    QLinearGradient linear(top, down);
    linear.setColorAt(0, QColor(0, 160, 255));
    linear.setColorAt(0.1, QColor(0, 190, 248));
    linear.setColorAt(0.4, QColor(255, 255, 255));
    linear.setColorAt(0.6, QColor(255, 255, 255));
    linear.setColorAt(0.9, QColor(0, 190, 248));
    linear.setColorAt(1, QColor(0, 160, 255));

    setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,QBrush(linear));
    setPalette(pal);

    connect(loginBtn,&QPushButton::clicked,this,&bottomWidget::slotLogin);
}

void bottomWidget::slotLogin()
{
    //qDebug()<<"login";
    emit sigLogin();
}

