#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <QDialog>
#include <map>
#include <vector>
#include "basedialog.h"
#include "userdefine.h"
#include "client_h/datatype.h"
#include "finddlg.h"
#include "classifyfriend.h"
#include "chatdlg.h"
class QMenu;
class friendTabBar;
class friendWidget;

namespace Ui {
class workStation;
}

QString readFile(QString name);

class workStation : public baseDialog
{
    Q_OBJECT

public:
    explicit workStation(QWidget *parent = 0);
    ~workStation();
    void setUserInfo(QString nick,QString signature,int level);
    void setHeadImage(QPixmap &pix);
    void addRecommend(userInfo& info);

    void addFriendBar(QString name,int total);
    void addFriend(QString barName,const userInfo& info,QPixmap& pix);
    classifyFriend*  getNoteWidget();
    void initNoteWidget(const QVector<groupInfo>& groups);
    // 显示提示信息
    void findDlgMes(QString mes);
    // 添加未查看的聊天信息数目
    void addFWMes(QString account,int num);
    // 清除未查看的聊天信息数目
    void clearFWMes(QString account);
    findDlg* getFindWidget();

    chatDlg* newChatDlg(QString account);
    chatDlg* getChatDlg(QString account);
    friendWidget* getFW(QString account);

protected:
    void initFriendBar();
    void widgetColumnChangeChecked();
    void addStateAction(QMenu *menu);

    void createStyleSheet();
    void slotToolBtnClose();

    bool eventFilter(QObject *obj, QEvent *e);
    void mousePressEvent(QMouseEvent *event);

protected slots:
    void slotContactPushBtn();
    void slotGroupPushBtn();
    void slotZonePushBtn();
    void slotStateChange();



private slots:
    void on_findUserBtn_clicked();

signals:
    void sigFindFriend();     // 显示添加好友界面后，向服务器发送推荐请求
    void sigAddFriend(int friendID);
    void sigFindPerson(QString str); //  发送查询请求,str是昵称/QQ号
    void sigStartChat(QString accunt);

private:
    void initChatVec();

    Ui::workStation *ui;
    userWin::winTabBar curtab;  //  widgetColumn里当前选中按钮
    userWin::userState curState;
    QMenu *stateMenu;
    std::map<QString,int> hx;
    std::vector<friendTabBar*> barVec;

    findDlg *findWidget;
    classifyFriend *noteWidget;

    QVector<chatDlg*> chatVec;
    QVector<friendWidget*> fwVec;
    int chatCnt=0;
};

#endif // WORKSTATION_H
