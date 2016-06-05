#include "chatdlg.h"
#include "ui_chatdlg.h"
#include "resources.h"
#include <QDebug>
#include <QDateTime>

chatDlg::chatDlg(QString account,QWidget *parent) :
    baseDialog(parent),
    ui(new Ui::chatDlg)
{
    ui->setupUi(this);

    setAutoFillBackground(true);
    createStyleSheet();
    broudGroundPixmap=new QPixmap(Resources::mainClassicBackground());
    broudGroundWidget=this;
    createTitleBar(ui->titleWidget,WindowToolClose | WindowToolMin,"QQ2016");

    ui->historyWidget->hide();
    _account = account;
    historyOffset = 0;
}

chatDlg::~chatDlg()
{
    delete ui;
}

void chatDlg::setNick(QString nick)
{
    ui->nickLab->setText(nick);
}

void chatDlg::addMes(QString mes, QDateTime& time)
{
    QString nick = ui->nickLab->text();
    QString str = time.toString("yyyy-MM-dd hh:mm");
    ui->mesEdit->append(str);
    ui->mesEdit->append(nick + " : " + mes );
}

void chatDlg::addHistoryMes( QString mes, QDateTime &time, QString nick)
{
    if (nick == "") nick = ui->nickLab->text();
    QString str = time.toString("yyyy-MM-dd hh:mm");
    ui->histroyEdit->append(str);
    ui->histroyEdit->append(nick + " : " + mes );
}

void chatDlg::createStyleSheet()
{
    qApp->setStyleSheet(readFile(":/qss/workstation.css"));
}

void chatDlg::slotToolBtnClose()
{
    close();
    emit sigClose(_account);
}

void chatDlg::on_sendBtn_clicked()
{
    if (ui->chatEdit->toPlainText()=="") {
        return ;
    }
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm");
    ui->mesEdit->append(str);
    ui->mesEdit->append(_nick +" : " +  ui->chatEdit->toPlainText() );
    QString mes =ui->chatEdit->toPlainText();
    ui->chatEdit->clear();
    emit sigChatContent(_account, mes);
}

void chatDlg::on_historyBtn_clicked()
{
    emit sigHistoryChat(_account,historyOffset);
    historyOffset+=20;
    ui->historyWidget->show();
}
