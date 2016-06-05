#include "recommendwidget.h"
#include "ui_recommendwidget.h"
#include <QDebug>
#include "client_h/datatype.h"

recommendWidget::recommendWidget(int id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recommendWidget)
{
    ui->setupUi(this);
    _id = id;
    ui->headLab->setScaledContents(true);
    ui->headLab->setFrameShape(QFrame::StyledPanel);

//    setAutoFillBackground(true);
//    QPalette pal(palette());
//    pal.setBrush(QPalette::Window,Qt::white);
//    setPalette(pal);
}

recommendWidget::~recommendWidget()
{
    delete ui;
}

void recommendWidget::setUserInfo(QString nick,QString headImage)
{
    ui->nickLab->setText(nick);
    ui->headLab->setPixmap(QPixmap( QString(":/userInfo/image/userInfo/")+headImage ));
}

void recommendWidget::setUserInfo(userInfo& info)
{
    ui->nickLab->setText(info.nick);
    if (info.pix!=NULL) {
        ui->headLab->setPixmap(*info.pix);
    }
    else {
        ui->headLab->setPixmap(QPixmap( QString(":/userInfo/image/userInfo/")+info.headImage ));
    }
}

void recommendWidget::on_addBtn_clicked()
{
    emit sigBtnMes();
    emit sigAddFriend(_id);
}
