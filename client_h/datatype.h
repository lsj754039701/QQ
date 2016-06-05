#ifndef DATATYPE
#define DATATYPE
#include <QString>
#include <QDateTime>
class QPixmap;

namespace queryType {
    enum ClientType {
        text,
        image,
        fileHead,
        fileBody,
        login,
        registe,
        recommend,
        addFriend,
        groupsize,
        friendGroup,
        findPerson,
        chat,
            textChat,
            imgChat,
            fileChat,
        offlineMes,
        history
    };

}

namespace respondType {
    enum ServerType {
        error,
        descriptor,
        loginOk,  // 登陆成功
        registeOk, // 注册成功
        recommendOk,
        friendGroupSize,
        friendGroup,
        addFriend,
        addFriendError,
        accountFind,
        nickFind,
        findPersonError,
        chat,
            textChat,
            imgChat,
            fileChat,
         offlineMes,
        history
    };
}

namespace userStateType {
    enum userState {
        offline,
        connected,
        online,
        login,
        registe
    };
//    QString userStateHx[] ={
//      "offline"  ,"connected","online","login",""
//    };
}

struct registerInfo{
    QString nick,pw;
};

struct userInfo {
    QString nick;
    QString signatrue;
    QString headImage;
    QString account;
    qint8 level;
    QPixmap *pix;
    qint32 id;
    qint8 state;
    userInfo() { pix=NULL; }
};

struct groupInfo {
    QString name;
    qint32 id,total;
    groupInfo() {}
};

struct chatMes
{
    QString  fromAccount,content,toAccount;
    QDateTime time;
    qint8 type;
};

#endif // DATATYPE

