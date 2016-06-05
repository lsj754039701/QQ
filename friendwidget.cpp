#include "friendwidget.h"
#include "ui_friendwidget.h"
#include "resources.h"
#include <QDebug>
#include <QContextMenuEvent>
#include <QMenu>

namespace respondType {
    QString userState[]={ "离线","", "在线" };
}

friendWidget::friendWidget(const userInfo& info,QPixmap& pix,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friendWidget)
{
    ui->setupUi(this);
   // ui->headLabel->setPixmap(QPixmap(Resources::userHeadImage()));
    ui->headLabel->setScaledContents(true);
 /*   setStyleSheet("QWidget{"
        "background:white;"
        "border-bottom:1px solid lightgrey;"
    "}"); */
    ui->nameLabel->setText(info.nick);
    ui->vipLabel->setText(QString("vip ")+QString::number(info.level));
    ui->stateLabel->setText( QString("[")+ respondType::userState[ info.state ]  +QString("] "));
    ui->signatrueLabel->setText(info.signatrue);
    ui->headLabel->setPixmap(pix);

    _account = info.account;
    ui->headLabel->setToolTip(_account);
    ui->mesLab->adjustSize();
    ui->mesLab->hide();
}

friendWidget::~friendWidget()
{
    delete ui;
}

int friendWidget::getMesTotal()
{
    return ui->mesLab->text().toInt();
}

void friendWidget::addMes(int num)
{
    int x = getMesTotal();
    ui->mesLab->setText(QString::number(x+num));
    if (num>0) ui->mesLab->show();
}

void friendWidget::clearMes()
{
    ui->mesLab->setText("0");
    ui->mesLab->hide();
}

void friendWidget::contextMenuEvent(QContextMenuEvent *e)
{
    QMenu *menu=new QMenu;
    QAction *reName=menu->addAction("修改备注名");
    QAction *move=menu->addAction("移动到其它分组");
    //menu->setStyleSheet("background:lightgrey;");
    menu->exec(QCursor::pos());
    delete menu;
}

void friendWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        qDebug()<<_account;
        emit sigStartChat(_account);
    }
    QWidget::mouseDoubleClickEvent(e);
}

