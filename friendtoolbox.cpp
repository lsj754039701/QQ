#include "friendtoolbox.h"
#include "resources.h"

friendToolBox::friendToolBox(QWidget *parent):QToolBox(parent)
{
    curIndex=0;  // my friends
    setCurrentIndex(curIndex);
    connect(this,SIGNAL(currentChanged(int)),this,SLOT(slotIndexChange(int)));
}

void friendToolBox::slotIndexChange(int index)
{
    setItemIcon(curIndex,QIcon(Resources::iconToolBoxNotSelected()));
    curIndex = index;
    setItemIcon(curIndex,QIcon(Resources::iconToolBoxSelected()));
}
