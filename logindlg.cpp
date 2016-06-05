#include "logindlg.h"
#include <QStackedLayout>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QEvent>
#include <QDebug>

loginDlg::loginDlg(QWidget *parent):QDialog(parent)
{
    init();
    initSlot();

    QWidget *widget=new QWidget;
    QGridLayout *grid=new QGridLayout;
    QHBoxLayout *hLayout=new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;

    grid->addWidget(account,0,0);
    grid->addWidget(pw,1,0);
    grid->addWidget(regietBtn,0,1);
    grid->addWidget(findPwBtn,1,1);

    hLayout->addWidget(remerberMe);
    hLayout->addWidget(remerberLab);
    hLayout->addWidget(autoLogin);
    hLayout->addWidget(autoLoginLab);
    hLayout->addStretch();
    hLayout->setContentsMargins(0,0,0,0);

    vLayout->addLayout(grid);
    vLayout->addSpacing(10);
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    QHBoxLayout *mainLayout=new QHBoxLayout;
    mainLayout->addWidget(userImage,0,Qt::AlignTop);
    mainLayout->addLayout(vLayout);

    QVBoxLayout *mainLayout2 = new QVBoxLayout;
    mainLayout2->addWidget(errorLab);
    mainLayout2->addLayout(mainLayout);

    widget->setLayout(mainLayout2);

//    stackLayout->addWidget(widget);

//    QVBoxLayout *mainLayout = new QVBoxLayout;
//    mainLayout->addLayout(stackLayout);
//    QWidget *contentWidget=new QWidget;
//    contentWidget->setLayout(mainLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topWidget);
    layout->addWidget(widget);
    layout->addWidget(downWidget);
    //layout->addWidget(loginBtn);

    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
}

QString loginDlg::getAccount()
{
    return account->text();
}

QString loginDlg::getPassword()
{
    return pw->text();
}

void loginDlg::setErrorLab(QString error)
{
    errorLab->setText(error);
}

void loginDlg::showMaxRestored()
{
    showMaximized();
}

void loginDlg::moveWidget(QPoint point)
{
    move(point);
}

bool loginDlg::eventFilter(QObject *obj, QEvent *e)
{
    if (obj==account) {
        if (e->type()==QEvent::FocusIn) {
            if (account->text()=="QQ号码") account->clear();
        }
        else if (e->type()==QEvent::FocusOut) {
            if (account->text()=="") account->setText("QQ号码");
        }
    }
    QDialog::eventFilter(obj,e);
}

void loginDlg::slotRegister()
{
    qDebug()<<"register";
    emit sigRegister();
}

void loginDlg::slotLogin()
{
    if ( getAccount()=="" ||  getPassword()=="") {
        setErrorLab("请输入账号或密码");
    }
    else emit sigLogin();
}


void loginDlg::init()
{
    resize(400,300);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

    topWidget = new titleWidget(0,"login");
    downWidget =  new bottomWidget;
    //stackLayout = new QStackedLayout(this);

    account=new QLineEdit;
    pw=new QLineEdit;
    regietBtn=new QToolButton;
    findPwBtn=new QToolButton;
    regietBtn->setIcon(QPixmap(":/login/image/zhuce_press.png"));
    findPwBtn->setIcon(QPixmap(":/login/image/mima.png"));
    int h = account->size().height();
    regietBtn->setIconSize(QSize(h,25));
    findPwBtn->setIconSize(QSize(h,25));
    regietBtn->setFixedWidth(80);
    findPwBtn->setFixedWidth(80);

    regietBtn->setStyleSheet("border-radius:2px;");
    findPwBtn->setStyleSheet("border-radius:2px;");
    account->setPlaceholderText("QQ号码/邮箱/电话号码");
    pw->setPlaceholderText("密码");

            account->setText("1000005");
            pw->setText("444");

    remerberMe = new QCheckBox;
    autoLogin = new QCheckBox;
    remerberLab=new QLabel;
    autoLoginLab=new QLabel;
    errorLab = new QLabel;
    errorLab->setFixedHeight(20);  //--------------
    errorLab->setStyleSheet("color:red");
    errorLab->setAlignment(Qt::AlignHCenter);
    remerberLab->setText(" 记住密码");
    autoLoginLab->setText(" 自动登陆");

    userImage=new QLabel;
    userImage->setPixmap(QPixmap(":/login/image/head.png"));
    userImage->setScaledContents(true);
    //userImage->resize(QSize(25,25));
    userImage->setMinimumSize(QSize(100,100));
    userImage->setMaximumSize(QSize(100,100));
    userImage->setFrameShape(QFrame::StyledPanel);
}

void loginDlg::initSlot()
{
    connect(topWidget,&titleWidget::moveWidget,this,&loginDlg::moveWidget);
    connect(topWidget,&titleWidget::closeWidget,this,&loginDlg::close);

    connect(downWidget,&bottomWidget::sigLogin,this,&loginDlg::slotLogin);
    connect(regietBtn,&QToolButton::clicked,this,&loginDlg::sigRegister);
}

