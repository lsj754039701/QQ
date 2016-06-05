#include "friendtabbar.h"
#include "ui_friendtabbar.h"
#include "friendwidget.h"
#include <QVBoxLayout>

friendTabBar::friendTabBar(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendTabBar)
{
    ui->setupUi(this);
    curVisable=false;
    layout=new QVBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    //layout->addStretch();
    ui->widget->setVisible(curVisable);
    ui->widget->setLayout(layout);
    cntFriends=0;
    ui->toolButton->setIcon(QIcon(":/workstation/image/maintabbar/0.png"));
    ui->toolButton->setText(name);
}

friendTabBar::~friendTabBar()
{
    delete ui;
}

void friendTabBar::addFriend(friendWidget *w)
{
    QVBoxLayout *wLayout= (QVBoxLayout*)ui->widget->layout();
    wLayout->insertWidget(cntFriends,w);
    cntFriends++;
    connect(w,&friendWidget::sigStartChat,this,&friendTabBar::sigStartChat);
}

QString friendTabBar::getName()
{
    return ui->toolButton->text();
}

void friendTabBar::on_toolButton_clicked()
{
    curVisable=!curVisable;
    ui->widget->setVisible(curVisable);
    QString str=curVisable?":/workstation/image/maintabbar/90.png":":/workstation/image/maintabbar/0.png";;
    ui->toolButton->setIcon(QIcon(str));
}
