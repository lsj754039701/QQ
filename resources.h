#ifndef RESOURCES_H
#define RESOURCES_H
#include <QString>
#include "userdefine.h"

class Resources
{
public:
    Resources();

    static QString mainWindowIcon();
    static QString userHeadImage();
    static QString mainAppBackground();
    static QString iconSignatureEdit();
    static QString iconSearchEdit();
    static QString iconToolBoxSelected();
    static QString iconToolBoxNotSelected();
    static QString userState(userWin::userState state);
    static QString mainClassicBackground();

};

#endif // RESOURCES_H
