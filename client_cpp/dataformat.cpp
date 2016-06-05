#include "client_h/dataformat.h"
#include "client_h/myclient.h"
#include <QByteArray>
#include <QDataStream>
#include <QVariant>
#include <QDateTime>

DataFormat::DataFormat()
{
    bufBlock = new QByteArray;
}

DataFormat::~DataFormat()
{
    delete bufBlock;
}

QByteArray* DataFormat::encodeLoginData(MyClient &client)
{
    bufBlock->resize(0);
    QString account,  pw;
    account =client.loginWidget->getAccount();
    pw = client.loginWidget->getPassword();

    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0) <<qint8(queryType::login)<< qint32(client.id )<<account<<pw;
    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeRegisterData(registerInfo info,qint32 id)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0) <<qint8(queryType::registe)<<qint32(id );
    in<<info.nick<<info.pw;
    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeRecommend(qint32 id,QString account)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0) <<qint8(queryType::recommend)<<qint32(id )<<account;
    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeAddFriend(QString account, qint32 friendID, qint32 descrip)
{
    bufBlock->resize(0);                   qDebug()<<"  encodeAddFriend "<<account<<" , "<<friendID;
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0) <<qint8(queryType::addFriend)<<account<<qint32(friendID);

    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeGroupOwer(QString account,qint8 type)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

     in<<qint32(0) <<type<<account;
     in.device()->seek(0);
     in<<qint32(bufBlock->size() - sizeof(qint32));
     return bufBlock;
}

QByteArray *DataFormat::encodeAddFriend(MyClient &client, qint32 friendID)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0) <<qint8(queryType::addFriend);
    in<<client._account<<friendID;
    in<<client.mainWidget->getNoteWidget()->getGroupName();
             //qDebug()<<"  encodeAddFriend "<<client._account<<" , "<<friendID;
             //qDebug()<<client.mainWidget->getNoteWidget()->getGroupName();
    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeFindPerson(MyClient &client, QString str)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0) <<qint8(queryType::findPerson);
    in<<client._account<<str;

    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeChatInfo(QMap<QString, QVariant>& hx)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0);
    in<<qint8(  hx["ontType"].toInt())<<qint8( hx["twoType"].toInt() ) ;
    in<<hx["fromAccount"].toString()<<hx["toAccount"].toString();
    in<<hx["content"].toString();
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    in<<time;

    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeOfflineMes(QString account)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0)<<qint8(queryType::offlineMes)<<account;

    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}

QByteArray *DataFormat::encodeHistroyChat(QString friendQQ, QString meQQ, int offset)
{
    bufBlock->resize(0);
    QDataStream in(bufBlock,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_5_0);

    in<<qint32(0)<<qint8(queryType::history)<<meQQ<<friendQQ<<qint8(offset);

    in.device()->seek(0);
    in<<qint32(bufBlock->size() - sizeof(qint32));
    return bufBlock;
}


