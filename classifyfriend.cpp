#include "classifyfriend.h"
#include "ui_classifyfriend.h"

classifyFriend::classifyFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::classifyFriend)
{
    ui->setupUi(this);
}

classifyFriend::~classifyFriend()
{
    delete ui;
}

QString classifyFriend::getGroupName()
{
    return ui->comboBox->currentText();
}

void classifyFriend::addGroup(QString name)
{
    ui->comboBox->addItem(name);
}

void classifyFriend::setFriendID(int friendid)
{
    friendID = friendid;
}

void classifyFriend::on_cancleBtn_clicked()
{
    close();
}

void classifyFriend::on_okBtn_clicked()
{
    emit sigAddFriend(friendID);
    close();
}
