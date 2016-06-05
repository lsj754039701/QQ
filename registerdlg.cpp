#include "registerdlg.h"
#include "ui_registerdlg.h"
#include "resources.h"
#include <QFile>
#include <QDebug>

registerDlg::registerDlg(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::registerDlg)
{
    ui->setupUi(this);
    state = false;  //现在是要登陆还是注册, ture:注册

    setAutoFillBackground(true);
    createStyleSheet();
    broudGroundPixmap=new QPixmap(Resources::mainAppBackground());
    broudGroundWidget=this;
    createTitleBar(ui->titleWidget,WindowToolClose | WindowToolMin,"QQ2016");
}

registerDlg::~registerDlg()
{
    delete ui;
}

void registerDlg::setErrorLab(QString str)
{
    ui->errorLab->setText(str);
}

void registerDlg::createStyleSheet()
{
    qApp->setStyleSheet(readFile(":/qss/workstation.css"));
}

void registerDlg::slotToolBtnClose()
{
    qApp->quit();
}



void registerDlg::on_registerBtn_clicked()
{
    state = true;
    if (ui->nickLab->text()=="" || ui->pwLine->text()=="" ||  ui->pwLine2->text()=="") {
        ui->errorLab->setText("请输入完整信息");
        return ;
    }
    if (ui->pwLine->text() != ui->pwLine2->text()) {
        ui->errorLab->setText("两次密码不一致");
        return ;
    }
    info.nick = ui->nickLab->text();
    info.pw = ui->pwLine->text();
    emit sigRegister();
}
