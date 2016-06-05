#include "resources.h"

Resources::Resources()
{

}

QString Resources::mainWindowIcon()
{
    return ":/login/image/menu_btn_highlight.png";

}

QString Resources::userHeadImage()
{
    return ":/login/image/head.png";
}

QString Resources::mainAppBackground()
{
    return ":/workstation/image/interface/default.jpg";
}

QString Resources::iconSignatureEdit()
{
    return ":/workstation/image/interface/autograph.png";
}

QString Resources::iconSearchEdit()
{
    return ":/workstation/image/interface/find_old.png";
}

QString Resources::iconToolBoxSelected()
{
    return ":/workstation/image/maintabbar/90.png";
}

QString Resources::iconToolBoxNotSelected()
{
    return ":/workstation/image/maintabbar/0.png";
}

QString Resources::userState(userWin::userState state)
{
    switch (state) {
    case userWin::online:
        return ":/state/image/state/imonline.png";
    case userWin::leave:
        return ":/state/image/state/away.png";
    case userWin::stealth:
        return ":/state/image/state/invisible.png";
    case userWin::notDisturb:
        return ":/state/image/state/busy.png";
    case userWin::offline:
        return ":/state/image/state/imoffline.png";
    }
    return "";
}

QString Resources::mainClassicBackground()
{
    return ":/workstation/image/interface/ClassicThemeBkg.jpg";
}











