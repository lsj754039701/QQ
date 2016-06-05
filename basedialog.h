#ifndef BASEDIALOG_H
#define BASEDIALOG_H
#include <QDialog>
#include <QToolButton>
#include <QLabel>

class baseDialog:public QDialog
{
public:
    baseDialog(QWidget *parent=0);
    ~baseDialog();
    enum windowFlag{
        WindowToolClose	= 1,
        WindowToolMax	= 2,
        WindowToolMin		= 4,
        WindowToolNor		= 8,
        WindowToolSkin	= 16,
        WindowToolSet		= 32,
        WindowToolIcon	= 64,
    };

protected slots:
    virtual void slotToolBtnClose();
    virtual void slotToolBtnMax();
    virtual void slotToolBtnMin();
    virtual void slotToolBtnNor();
    virtual void slotToolBtnSet() {}
    virtual void slotToolBtnSkin() {}

protected:
    virtual void createTitleBar(QWidget *parent,int flag,QString title = "");
    virtual void resizeEvent(QResizeEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

    QToolButton *btnClose;
    QToolButton *btnMax;
    QToolButton *btnMin;
    QToolButton *btnNor;
    QToolButton *btnSet;
    QToolButton *btnSkin;
    QLabel *logoLable;
    QLabel *titleLable;
    bool isPress;
    QPoint clickPos;
    QPixmap *broudGroundPixmap;
    QWidget *broudGroundWidget;
};

#endif // BASEDIALOG_H
