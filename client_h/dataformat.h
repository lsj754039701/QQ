#ifndef DATAFORMAT
#define DATAFORMAT
class QByteArray;
class MyClient;
class QVariant;
#include <QMap>
#include "client_h/datatype.h"

enum dataType {
    text,
    image,
    fileHead,
    fileBody,
    login
};

class DataFormat
{
public:
    DataFormat();
    ~DataFormat();
    QByteArray* encodeLoginData(MyClient& client);
    QByteArray* encodeRegisterData(registerInfo info,qint32 id);
    //QByteArray* decodeLoginData(QByteArray &data,MyClient &client);
    QByteArray* encodeRecommend(qint32 id,QString account);
    QByteArray* encodeAddFriend(QString account,qint32 friendID,qint32 descrip);

    QByteArray* encodeGroupOwer(QString account,qint8 type);
    QByteArray* encodeAddFriend(MyClient& client,qint32 friendID);
    QByteArray* encodeFindPerson(MyClient& client,QString str);
    QByteArray* encodeChatInfo(QMap<QString,QVariant>& hx );
    QByteArray* encodeOfflineMes(QString account );

    QByteArray* encodeHistroyChat(QString friendQQ, QString meQQ, int offset);
private:
    QByteArray *bufBlock;
};

#endif // DATAFORMAT

