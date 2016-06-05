#include "logindlg.h"
#include <QApplication>
//#include "workstation.h"
//#include "registerdlg.h"
//#include "recommendwidget.h"
//#include "finddlg.h"
//#include "classifyfriend.h"
#include "chatdlg.h"
#include "client_h/myclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    loginDlg d;
//    d.show();
//    workStation w;
//    w.show();

    MyClient client,c2;
    client.showLoginWidget();
    c2.showLoginWidget();
    //c3.showLoginWidget();
    //c4.showLoginWidget();

//    chatDlg dlg;
//    dlg.show();
    return a.exec();
}

