#ifndef MYCLIENT
#define MYCLIENT

#include "logindlg.h"
#include "registerdlg.h"
#include "workstation.h"

#include <QObject>
#include <QTcpSocket>
class  DataFormat;

class MyClient:public QObject
{
    Q_OBJECT
public:
    friend class DataFormat;
    explicit MyClient(QObject *parent=0);
    void showMainWidget();
    void showLoginWidget();
    void registerOK(QDataStream &in);
    void recommendOk(QDataStream &in);
    void getGroupSize(QDataStream &in);   //    获取用户的好友分组信息，包括分组总数，分组名，分组下好友数目
    void getFriends(QDataStream &in);   // 获取某个分组下所有好友
    QPixmap getHeadImage(qint32 headsize);
    void getAddFriend(QDataStream &in);

    void accountFindPerson(QDataStream &in);
    void nickFindPerson(QDataStream &in);
    int getGroupIndex(QString groupName,QString account);

    void textChat(QDataStream &in);
    void offlineChatMes(QDataStream &in);
    void getHistoryChat(QDataStream &in);

signals:
    void sigLogin();

public slots:
    void slotConnectToHost();
    void slotLogin();
    void slotRegister(registerInfo info);
    void slotDisconnect();
    void slotReadyRead();
    void slotToRegisterDlg();
    void setErrorLab(QString str) { loginWidget->setErrorLab(str); }
    void slotRecommend();   // 好友推荐
    void slotAddFriend(int friendID);   // 添加好友

    void slotFindPerson(QString str);
    void slotStartChat(QString account);
    void slotChatContent(QString toAccount,QString content);
    void slotChatClose(QString account);

    void slotHistoryChat(QString account,int offset);

private:
    bool createDir(QString path="");

    loginDlg *loginWidget;
    registerDlg *registerWidget;
    workStation *mainWidget;
    QTcpSocket *socket;
    DataFormat *format;
    qint32 blocksize;

    qint8 _state;
    qint32 id;
    QByteArray bufBlock;
    QString _account,_nick;
    QMap<QString,QVector<userInfo> > _groups;
    QVector<groupInfo> _groupInfo;

    userInfo _info;
    QMap<QString,QString> actToGroup;
    QMap<QString,QVector<chatMes> > mesVec;
    QMap<QString,bool> isChated;
};

#endif // MYCLIENT

