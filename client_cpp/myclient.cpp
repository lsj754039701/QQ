#include "client_h/myclient.h"
#include "client_h/dataformat.h"
#include "client_h/datatype.h"

#include <QDebug>
#include <QHostAddress>
#include <QBuffer>
#include <QImageReader>
#include <QDir>
#include <QVariant>
#include <QDateTime>

MyClient::MyClient(QObject *parent):QObject(parent)
{
    loginWidget = new loginDlg;
    registerWidget = new registerDlg;
    socket = new QTcpSocket;
    mainWidget = new workStation;
    format = new DataFormat;
    blocksize=0;
    _state = userStateType::offline;

     //连接服务器成功，发射登陆信号
    connect(this,&MyClient::sigLogin,this,&MyClient::slotLogin);
    connect(socket,&QTcpSocket::disconnected,this,&MyClient::slotDisconnect);
    connect(socket,&QTcpSocket::readyRead,this,&MyClient::slotReadyRead);
    connect(loginWidget , &loginDlg::sigLogin ,this, &MyClient::slotConnectToHost);
    connect(loginWidget,&loginDlg::sigRegister,this,&MyClient::slotToRegisterDlg);
    connect(registerWidget,&registerDlg::sigRegister,this,&MyClient::slotConnectToHost);

    connect(mainWidget,&workStation::sigFindFriend,this,&MyClient::slotRecommend); // 好友推荐
    connect(mainWidget,SIGNAL(sigAddFriend(int)),this,SLOT(slotAddFriend(int)));    // 添加好友
    connect(mainWidget,&workStation::sigFindPerson,this,&MyClient::slotFindPerson);

    connect(mainWidget,&workStation::sigStartChat,this,&MyClient::slotStartChat);
}

// 这里有个bug ， 若用户注册失败，再去登陆的话会有问题
void MyClient::slotConnectToHost()
{
    if (_state == userStateType::offline)
        socket->connectToHost( QHostAddress::LocalHost  ,8000);
    else if (registerWidget->getState()) {
        slotRegister(registerWidget->getRegisterInfo());
    }
    else  {
        slotLogin();
    }
}

void MyClient::slotLogin()
{                                           // qDebug()<<socket->socketDescriptor() <<" "<<"连接服务器成功，正在登陆中......";
    loginWidget->setErrorLab("正在登陆中......");
    QByteArray *data = format->encodeLoginData(*this);
    socket->write(*data);
}

void MyClient::slotRegister(registerInfo info)
{
    QByteArray *data = format->encodeRegisterData(info,id);
    loginWidget->setErrorLab("正在注册中......");
    socket->write(*data);
}

void MyClient::slotDisconnect()
{
    loginWidget->setErrorLab(" slotDisconnect ");
    _state = userStateType::offline;
}

// 接收服务器的响应
void MyClient::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    if (blocksize == 0) {
        if (socket->bytesAvailable() < sizeof(qint32)) return ;
        in>>blocksize;
    }
    if (socket->bytesAvailable() < blocksize) return ;                                    

    qint8 type;
    in>>type;                                      qDebug()<<" type="<<type;
    if (type == respondType::error) {   // 错误信息
        QString str;
        in>>str;
        if (registerWidget->getState()) {
            registerWidget->setErrorLab(str);
        }
        else {
            loginWidget->setErrorLab(str);
        }
    }
    else if (type == respondType::descriptor) {  // 连接服务器成功
        in>>id;
        _state = userStateType::connected;
        if (registerWidget->getState()) {
            slotRegister(registerWidget->getRegisterInfo());
        }
        else  emit sigLogin();
    }
    else if(type == respondType::loginOk) {      //  登陆成功
        QString nick,signature;
        qint8 level,state;
        qint32 headsize;
        in>>nick>>level>>signature>>state>>headsize;
        QPixmap pix = getHeadImage(headsize);
        mainWidget->setUserInfo(nick,signature,level);
        mainWidget->setHeadImage(pix);
        _state = state;
        _account = loginWidget->getAccount();  //  得到账号
        _nick = nick;

        loginWidget->close();
        showMainWidget();
        bufBlock.resize(0);

        // 请求好友分组信息
        QByteArray *data = format->encodeGroupOwer(_account,queryType::groupsize);
        socket->write(*data);
    }
    else if (type == respondType::registeOk) {
        registerOK(in);
       _state = userStateType::online;
       // 请求好友分组信息
       QByteArray *data = format->encodeGroupOwer(_account,queryType::groupsize);
       socket->write(*data);
    }
    else if (type == respondType::recommendOk) {
        recommendOk(in);
    }
    else if(type == respondType::friendGroupSize) {
        getGroupSize(in);
    }
    else if(type == respondType::friendGroup) {
        for (int i=0;i<_groupInfo.count();i++) {
            getFriends(in);
        }
    }
    else if(type == respondType::addFriend) {
        getAddFriend(in);
    }
    else if (type == respondType::addFriendError) {
        QString error;
        in>>error;
        mainWidget->findDlgMes(error);
    }
    else if (type == respondType::accountFind) {
        accountFindPerson(in);
    }
    else if (type == respondType::nickFind) {
        nickFindPerson(in);
    }
    else if (type == respondType::findPersonError) {
        QString error;
        in>>error;
        mainWidget->findDlgMes(error);
    }
    else if (type == respondType::chat) {
        qint8 twotype;
        in>>twotype;
        if (twotype == respondType::textChat) {
            textChat(in);
        }
    }
    else if (type == respondType::offlineMes) {
        qint8 onetype;
        in>>onetype;
        if (onetype == respondType::chat) {
            offlineChatMes(in);
        }
    }
    else if (type == respondType::history) {
        qint8 onetype;
        in>>onetype;
        getHistoryChat(in);
    }
    blocksize = 0;
}

void MyClient::slotToRegisterDlg()
{
    loginWidget->close();
    registerWidget->show();
}

void MyClient::slotRecommend()
{
    QByteArray *data = format->encodeRecommend(id,_account);
    socket->write(*data);
}

void MyClient::slotAddFriend(int friendID)
{
    QByteArray *data = format->encodeAddFriend(*this,friendID);
    socket->write(*data);
}

void MyClient::slotFindPerson(QString str)
{
    QByteArray *data = format->encodeFindPerson(*this,str);
    socket->write(*data);
}

// 打开聊天窗口并设置聊天窗口的属性值，如对方昵称，字节昵称等等
void MyClient::slotStartChat(QString account)
{
    if (isChated.contains(account)) return ;
    isChated[account]=true;

    chatDlg *dlg = mainWidget->newChatDlg(account);
    connect(dlg,&chatDlg::sigChatContent,this,&MyClient::slotChatContent);
    connect(dlg,&chatDlg::sigClose,this,&MyClient::slotChatClose);

    connect(dlg,&chatDlg::sigHistoryChat,this,&MyClient::slotHistoryChat);

    QString groupName = actToGroup[account] ;
    int index = getGroupIndex(groupName,account);
    dlg->setNick( _groups[ groupName][index].nick );
    dlg->setMeNick(_nick);

    // 有无离线消息
    if (mesVec[account].count()>0) {
        for (int i=0;i<mesVec[account].count();i++) {
            dlg->addMes(mesVec[ account ][i].content, mesVec[ account ][i].time);
        }
        mesVec[ account ].clear();
        mainWidget->clearFWMes(account);
    }
}

void MyClient::slotChatContent(QString toAccount, QString content)
{
    QMap<QString,QVariant> hx;
    hx["toAccount"]=toAccount;
    hx["fromAccount"] = _account;
    hx["content"]  = content ;
    hx["ontType"] = queryType::chat;
    hx["twoType"] = queryType::textChat;    //  应由参数传递进来的

    QByteArray *data = format->encodeChatInfo(hx);
    socket->write(*data);
}

void MyClient::slotChatClose(QString account)
{
    isChated.remove(account);
}

void MyClient::slotHistoryChat(QString account, int offset)
{
    QByteArray *data = format->encodeHistroyChat(account, _account ,offset);
    socket->write(*data);
}

bool MyClient::createDir(QString path)
{
    QDir dir;
    if (path=="") {
        path = dir.currentPath();
        path = path.left( path.lastIndexOf("/") ) + QString("/qqV2/userImage");
    }
    if (dir.exists(path)) return false;
    return dir.mkdir(path);
}

void MyClient::showMainWidget()
{
    mainWidget->show();
}

void MyClient::showLoginWidget()
{
    loginWidget->show();
}

void MyClient::registerOK(QDataStream &in)
{
    qint64 account;
    qint8 level;
    QString signature,imageUrl;
    in>>account>>level>>signature>>imageUrl;
    registerInfo info = registerWidget->getRegisterInfo();
    mainWidget->setUserInfo(info.nick,signature,level);
    QPixmap pix(QString(":/userInfo/image/userInfo/")+imageUrl);
    mainWidget->setHeadImage(pix);

    registerWidget->close();
    showMainWidget();
    bufBlock.resize(0);

    _account = QString::number(account);  //  得到账号
    // 请求好友分组信息
    QByteArray *data = format->encodeGroupOwer(_account,queryType::groupsize);
    socket->write(*data);
}

void MyClient::recommendOk(QDataStream &in)
{
    qint8 limit ;
    in>>limit;
    userInfo info;
    for (int i=0;i<limit;i++) {
        in>>info.id>>info.nick;
        QPixmap pix;
        in>>pix;
        info.pix = &pix;
        //qDebug()<<"recommendOk:  "<<info.nick<<" , "<<info.headImage;
        mainWidget->addRecommend(info);
    }
}

void MyClient::getGroupSize(QDataStream &in)
{
    qint8 groupsize;
    in>>groupsize;
    for (int i=0;i<groupsize;i++) {
        groupInfo info;
        in>>info.total >>info.name;
        _groupInfo.push_back(info);
        _groups[ info.name ].resize( info.total );
        mainWidget->addFriendBar(info.name,info.total);
    }
    mainWidget->initNoteWidget(_groupInfo);
    // 请求分组下好友信息
    QByteArray *data = format->encodeGroupOwer(_account,queryType::friendGroup);
    socket->write(*data);
}

void MyClient::getFriends(QDataStream &in)
{
    QString name;
    in>>name;
    int len = _groups[ name ].count();
   // qDebug()<<" groups "<<_groups[ name ].count()<<" "<<name;
    for (int i=0;i<len;i++) {
        userInfo info;
        qint8 level;
        in>>info.account>>info.nick>>level>>info.signatrue>>info.state;
        QPixmap pix;
        info.level = level;
        in>>pix;
        //_groups[ name ].push_back(info);
        _groups[ name ][i]=info;
        mainWidget->addFriend(name,info,pix);

        actToGroup[info.account] = name;
    }

    QByteArray *data = format->encodeOfflineMes(_account);
    socket->write(*data);
}

QPixmap MyClient::getHeadImage(qint32 headsize)
{
    bufBlock.resize(0);
    bufBlock  = socket->read(headsize);
    QBuffer buffer(&bufBlock);
    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer,"png");
    QImage img=reader.read();
    QPixmap pix=QPixmap::fromImage(img);
    bufBlock.resize(0);
    return pix;
}

void MyClient::getAddFriend(QDataStream &in)
{
    userInfo info;
    // server::makeUserInfo(info,state,type)
    in>>info.account>>info.nick>>info.level>>info.signatrue>>info.state;
    QPixmap pix;
    in>>pix;
    mainWidget->findDlgMes("好友添加成功");
    mainWidget->addFriend( mainWidget->getNoteWidget()->getGroupName(),info,pix );
}

void MyClient::accountFindPerson(QDataStream &in)
{
    qint8 total;
    in>>total>>_info.id >>_info.nick;
    QPixmap pix;
    in>>pix;
    _info.pix = &pix;
    mainWidget->getFindWidget()->clearRecomment();
    mainWidget->addRecommend(_info);
}

void MyClient::nickFindPerson(QDataStream &in)
{
    qint8 total;
    in>>total;
    userInfo info;
    mainWidget->getFindWidget()->clearRecomment();
    for (int i=0;i<total;i++) {
        in>>info.id>>info.nick;
        QPixmap pix;
        in>>pix;
        info.pix = &pix;
        mainWidget->addRecommend(info);
    }
}

int MyClient::getGroupIndex(QString groupName, QString account)
{
    for (int i=0;i<_groups[groupName].count();i++) {
        if (_groups[groupName][i].account == account){
            return i;
        }
    }
    return -1;
}

void MyClient::textChat(QDataStream &in)
{
    chatMes mes;
    in>>mes.fromAccount>>mes.content;
    in>>mes.time;
    if (isChated.contains(mes.fromAccount)) {
        chatDlg *dlg = mainWidget->getChatDlg(mes.fromAccount);
        dlg->addMes(mes.content,mes.time);
    }
    else {
        mesVec[mes.fromAccount].push_back(mes);
        mainWidget->addFWMes(mes.fromAccount,1);
    }
}

void MyClient::offlineChatMes(QDataStream &in)
{
    qint8 total;
    in>>total;
    chatMes mes;
    for (int i=0;i<total;i++) {
        in>>mes.fromAccount>>mes.type;
        if (mes.type == queryType::textChat) {
            in>>mes.content;
        }
        in>>mes.time;
        mesVec[mes.fromAccount].push_back(mes);
    }
    mainWidget->addFWMes(mes.fromAccount,total);
}

void MyClient::getHistoryChat(QDataStream &in)
{
    qint8 total;
    in>>total;
    chatMes mes;
    chatDlg *dlg;
    QVector<chatMes> vec;
    for (int i=0;i<total;i++) {
        in>>mes.fromAccount>>mes.type;
        if (mes.type == queryType::textChat) {
            in>>mes.content;
        }
        in>>mes.time;
        vec.push_back(mes);
    }
    for (int i=0;i<total;i++) if (vec[i].fromAccount != _account) {
        dlg = mainWidget->getChatDlg(vec[i].fromAccount);
        break;
    }
    for (int i=0;i<total;i++) {
        if (vec[i].fromAccount == _account)
             dlg->addHistoryMes(vec[i].content,vec[i].time,_nick);
        else dlg->addHistoryMes(vec[i].content,vec[i].time);
    }

}
       //-------------------------1000005     444

