#include "workstation.h"
#include "ui_workstation.h"
#include "friendwidget.h"
#include "recommendwidget.h"
#include "friendtabbar.h"
#include "resources.h"


#include <QDebug>
#include <QFile>
#include <QPushButton>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QMenu>

#define SIGNATURE "编辑个性签名"

workStation::workStation(QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::workStation)
{
    ui->setupUi(this);
    curtab=userWin::contactBar;
    curState=userWin::online;     //    后期在登陆后获取
    stateMenu=NULL;
    addStateAction(stateMenu);
    initFriendBar();

    initChatVec(); // bad idea ,but ....
    findWidget = new findDlg(this);
    noteWidget = new classifyFriend(this);

    setAutoFillBackground(true);
    createStyleSheet();
    broudGroundPixmap=new QPixmap(Resources::mainAppBackground());
    broudGroundWidget=this;
    createTitleBar(ui->titleWidget,WindowToolClose | WindowToolMin | WindowToolSkin,"QQ2016");

    ui->tabWidget->tabBar()->setVisible(false);
    ui->nickLab->adjustSize();

    ui->headLabel->setFrameShape(QFrame::StyledPanel);
    ui->headLabel->setScaledContents(true);
    ui->headLabel->setPixmap(QPixmap(Resources::userHeadImage()));

    ui->mySeacherEdit->setMinimumWidth(283);
    ui->mySeacherEdit->setMaximumWidth(283);
    ui->myLineSignatrue->setMinimumWidth(139);
    ui->myLineSignatrue->setMaximumWidth(139);
    ui->myLineSignatrue->setLablePic(Resources::iconSignatureEdit());
    ui->mySeacherEdit->setLablePic(Resources::iconSearchEdit());
    ui->myLineSignatrue->setLineStyle(readFile(":/qss/lineSignature.css"));
    ui->myLineSignatrue->setToolTip(ui->myLineSignatrue->text());
    ui->mySeacherEdit->setLineStyle(readFile(":/qss/lineSearch.css"));

    //ui->weatherLabel->installEventFilter(this);

    connect(ui->contactPushBtn,&QPushButton::clicked,this,&workStation::slotContactPushBtn);
    connect(ui->groupPushBtn,&QPushButton::clicked,this,&workStation::slotGroupPushBtn);
    connect(ui->zonePushBtn,&QPushButton::clicked,this,&workStation::slotZonePushBtn);

    //connect(findWidget,SIGNAL(sigAddFriend(int)),this,SIGNAL(sigAddFriend(int)));  // 往上抛好友ID
    connect(findWidget,&findDlg::sigAddFriend ,[&](int friendID){
        noteWidget->setFriendID(friendID);
        noteWidget->show();
    } );
    connect(noteWidget,&classifyFriend::sigAddFriend,this,&workStation::sigAddFriend);

    connect(findWidget,&findDlg::sigFindFriend,this,&workStation::sigFindPerson);
}

workStation::~workStation()
{
    delete ui;
    delete findWidget;
}

void workStation::setUserInfo(QString nick, QString signature, int level)
{
    ui->nickLab->setText(nick);
    ui->myLineSignatrue->setText(signature);
}

void workStation::setHeadImage(QPixmap &pix)
{
    ui->headLabel->setPixmap(pix);
}

void workStation::addRecommend(userInfo& info)
{
    recommendWidget *w=new recommendWidget(info.id);
    w->setUserInfo(info);
    findWidget->addRecomdWidget(w);

    w->setAutoFillBackground(true);
    QPalette pal(w->palette());
    pal.setBrush(QPalette::Window,Qt::white);
    w->setPalette(pal);
}

void workStation::addFriendBar(QString name, int total)
{
    QVBoxLayout *layout =(QVBoxLayout*)ui->friendBarWidget->layout();
    friendTabBar *bar = new friendTabBar(name);
    barVec.push_back( bar);
    layout->insertWidget(barVec.size()-1,barVec.back());
    connect(bar,&friendTabBar::sigStartChat,this,&workStation::sigStartChat);
}

void workStation::addFriend(QString barName,const userInfo &info, QPixmap &pix)
{
    for (int i=0;i<barVec.size();i++) if (barVec[i]->getName() ==  barName) {
        friendWidget *fw = new friendWidget(info,pix);
        barVec[i]->addFriend(fw);
        fwVec.push_back(fw);
        break;
    }
}

classifyFriend* workStation::getNoteWidget()
{
    return noteWidget;
}

void workStation::initNoteWidget(const QVector<groupInfo> &groups)
{
    for (int i=0;i<groups.count();i++) {
        noteWidget->addGroup(groups[i].name);
    }
}

void workStation::findDlgMes(QString mes)
{
    findWidget->setMesLab(mes);
}

void workStation::addFWMes(QString account, int num)
{
    friendWidget *fw = getFW(account);
    fw->addMes(num);
}

void workStation::clearFWMes(QString account)
{
    friendWidget *fw = getFW(account);
    fw->clearMes();
}

findDlg *workStation::getFindWidget()
{
    return findWidget;
}

chatDlg *workStation::newChatDlg(QString account)
{
    for (int i=0;i<chatVec.count();i++) if (chatVec[i]->getAccount()==account) {
        chatVec[i]->show();
        return chatVec[i];
    }
    chatVec[chatCnt]->show();
    chatVec[chatCnt]->setAccount(account);
    return chatVec[chatCnt++];
}

chatDlg *workStation::getChatDlg(QString account)
{
    for (int i=0;i<chatVec.count();i++) if (chatVec.at(i)->getAccount() == account)  {
        return chatVec[i];
    }
}

friendWidget *workStation::getFW(QString account)
{
    for (int i=0;i<fwVec.count();i++) if (fwVec.at(i)->getAccount() == account)  {
        return fwVec[i];
    }
}

void workStation::initFriendBar()
{
    QVBoxLayout *layout=(QVBoxLayout*)ui->friendBarWidget->layout();
    //layout->addStretch();
    QLabel *lab = new QLabel;
    lab->hide();
    layout->addWidget(lab);
    layout->addStretch();

//    barVec.push_back(new friendTabBar("我的好友"));
//    barVec.push_back(new friendTabBar("陌生人"));
//    barVec.push_back(new friendTabBar("黑名单"));
//    layout->insertWidget(barVec.size()-1,barVec[0]);
//    layout->insertWidget(barVec.size()-1,barVec[1]);
//    layout->insertWidget(barVec.size()-1,barVec[2]);

//    layout->addStretch();
//    layout->setContentsMargins(0,0,0,0);
//    layout->setSpacing(0);
//    ui->friendBarWidget->setLayout(layout);

//    hx["我的好友"]=0;
//    hx["陌生人"]=1;
//    hx["黑名单"]=2;

//    for (int i=0;i<3;i++) {
//        for (int j=0;j<(i+1)*10;j++) {
//            barVec[i]->addFriend(new friendWidget);
//        }
//    }
}

void workStation::widgetColumnChangeChecked()
{
    ui->contactPushBtn->setChecked(userWin::contactBar==curtab);
    ui->groupPushBtn->setChecked(userWin::groupBar==curtab);
    ui->zonePushBtn->setChecked(userWin::zoneBar==curtab);
}

void workStation::addStateAction(QMenu *menu)
{
    if (menu==NULL) {
        menu = new QMenu(ui->stateToolBtn);
        ui->stateToolBtn->setMenu(menu);
    }
    QAction *action = NULL;
    QStringList list;
    list<<tr("在线")<<tr("离开")<<tr("隐身")
        <<tr("请勿打扰")<<tr("离线");
    for (int i=1;i<=list.count();i++) {
        action=menu->addAction(QIcon( Resources::userState( (userWin::userState)i ) ),
                               list.at(i-1),this,SLOT(slotStateChange()));
        action->setData(i);
    }
    ui->stateToolBtn->setIcon(QIcon(Resources::userState(curState)));
}

void workStation::createStyleSheet()
{
    qApp->setStyleSheet(readFile(":/qss/workstation.css"));
}

void workStation::slotToolBtnClose()
{
    qApp->quit();
}

bool workStation::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->weatherLabel) {
         if (e->type() == QEvent::Enter) {

         }
    }
    return baseDialog::eventFilter(obj,e);
}

void workStation::mousePressEvent(QMouseEvent *event)
{
    ui->myLineSignatrue->clearFocus();
    ui->mySeacherEdit->clearFocus();
    baseDialog::mousePressEvent(event);
}

void workStation::slotContactPushBtn()
{
    curtab=userWin::contactBar;
    widgetColumnChangeChecked();
    ui->tabWidget->setCurrentWidget(ui->contactTab);

}

void workStation::slotGroupPushBtn()
{
    curtab=userWin::groupBar;
    widgetColumnChangeChecked();
    ui->tabWidget->setCurrentWidget(ui->groupTab);
}

void workStation::slotZonePushBtn()
{
    curtab=userWin::zoneBar;
    widgetColumnChangeChecked();
    ui->tabWidget->setCurrentWidget(ui->zoneTab);
}

void workStation::slotStateChange()
{
    QAction *action=(QAction*)sender();
    ui->stateToolBtn->setIcon( QIcon(Resources::userState( (userWin::userState)action->data().toInt() )) );
}


void workStation::on_findUserBtn_clicked()
{
    findWidget->show();
    emit sigFindFriend();
}

void workStation::initChatVec()
{
    int n=5;
    for (int i=0;i<n;i++) {
        chatVec.push_back(new chatDlg);
    }
}

QString readFile(QString name)
{
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"qssFile open fail:"<<file.errorString();
        return "";
    }
    else return file.readAll();
}
