#ifndef FRIENDTOOLBOX_H
#define FRIENDTOOLBOX_H
#include <QToolBox>

class friendToolBox:public QToolBox
{
    Q_OBJECT
public:
    friendToolBox(QWidget *parent=0);


protected slots:
    void slotIndexChange(int index);

private:
    int curIndex;
};

#endif // FRIENDTOOLBOX_H
