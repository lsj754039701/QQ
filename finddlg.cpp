#include "finddlg.h"
#include "ui_finddlg.h"
#include "resources.h"
#include <QFile>
#include <QDebug>

findDlg::findDlg(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::findDlg)
{
    ui->setupUi(this);
    mesLab = new messageLab(this);//  消息标签初始化

    ui->tabWidget->tabBar()->setVisible(false);
    setAutoFillBackground(true);
    createStyleSheet();
    broudGroundPixmap=new QPixmap(Resources::mainAppBackground());
    broudGroundWidget=this;
    createTitleBar(ui->titleWidget,WindowToolClose | WindowToolMin,"QQ2016");
}

findDlg::~findDlg()
{
    delete ui;
    for (int i=0;i<vec.count();i++) delete vec.at(i);
    delete mesLab;
}

void findDlg::addRecomdWidget(recommendWidget *w)
{
    vec.append(w);
    ui->peopleLayout->addWidget(w);
    connect(w,SIGNAL(sigAddFriend(int)),this,SIGNAL(sigAddFriend(int)));

//    connect(w,&recommendWidget::sigBtnMes,[&](){
//        mesLab->move(width()/2,height()/2);
//        mesLab->message("添加好友成功");
//    });

    w->setMaximumHeight(ui->peopleWidget->height());
    w->setMaximumWidth(ui->peopleWidget->height()+110);
    w->show();
}

void findDlg::setMesLab(QString mes)
{
    mesLab->move(width()/2,height()/2);
    mesLab->message(mes);
}

void findDlg::clearRecomment()
{
    for (int i=0;i<vec.count();i++){
        vec[i]->hide();
        delete vec[i];
    }
    vec.clear();
}

void findDlg::createStyleSheet()
{
    qApp->setStyleSheet(readFile(":/qss/workstation.css"));
}

void findDlg::slotToolBtnClose()
{
    close();
    clearRecomment();
}

void findDlg::on_findPersonBtn_clicked()
{
    if (ui->findEdit->text()=="") {
        mesLab->move(width()/2,height()/2);
        mesLab->message("请输入搜索条件");
        return ;
    }
    emit sigFindFriend(ui->findEdit->text());
}
