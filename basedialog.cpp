#include "basedialog.h"
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMouseEvent>
#include <QDebug>
#include <QPalette>
#include "resources.h"

baseDialog::baseDialog(QWidget *parent):QDialog(parent)
{
    isPress = false;

    btnClose = NULL;
    btnMax = NULL;
    btnMin = NULL;
    btnNor = NULL;
    btnSet = NULL;
    btnSkin = NULL;
    logoLable = NULL;
    titleLable = NULL;
    broudGroundPixmap=NULL;
    broudGroundWidget=NULL;

    //setFocusPolicy(Qt::ClickFocus);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool );
    setMouseTracking(true);
}

baseDialog::~baseDialog()
{
    if (broudGroundPixmap) delete broudGroundPixmap;
    broudGroundPixmap=NULL;

    if (btnClose) delete btnClose;
    btnClose = NULL;

    if (btnMax) delete btnMax;
    btnMax = NULL;

    if (btnMin) delete btnMin;
    btnMin = NULL;

    if (btnNor) delete btnNor;
    btnNor = NULL;

    if (btnSet) delete btnSet;
    btnSet = NULL;

    if (btnSkin) delete btnSkin;
    btnSkin = NULL;

    if (logoLable) delete logoLable;
    logoLable = NULL;

    if (titleLable) delete titleLable;
    titleLable = NULL;
}

void baseDialog::slotToolBtnClose()
{
    close();
}

void baseDialog::slotToolBtnMax()
{
    btnMax->setVisible(false);
    btnNor->setVisible(true);
    showMaximized();
}

void baseDialog::slotToolBtnMin()
{
    showMinimized();
}

void baseDialog::slotToolBtnNor()
{
    btnMax->setVisible(true);
    btnNor->setVisible(false);
    showNormal();
}

void baseDialog::createTitleBar(QWidget *parent, int flag, QString title)
{
    if (parent==NULL) return ;
    parent->setMaximumHeight(20);
    parent->setMinimumHeight(20);
    QHBoxLayout *layout=new QHBoxLayout(parent);

    if ((flag & WindowToolIcon)==WindowToolIcon) {
        logoLable=new QLabel(parent);
        logoLable->setPixmap( QPixmap(Resources::mainWindowIcon()).scaled(20,20) );
        layout->addWidget(logoLable);
    }

    if (!title.isEmpty()) {
        titleLable = new QLabel(title,parent);
        layout->addWidget(titleLable);
    }
    layout->addStretch();
    //layout->addSpacerItem(new QSpacerItem(40,20,QSizePolicy::Expanding,QSizePolicy::Minimum) );

    if ((flag & WindowToolSkin)==WindowToolSkin) {
        btnSkin = new QToolButton(parent);
        btnSkin->setObjectName("btnSkin");
        btnSkin->setAutoRaise(true);
        connect(btnSkin,&QToolButton::clicked,this,&baseDialog::slotToolBtnSkin);
        layout->addWidget(btnSkin);
    }

    if ((flag & WindowToolSet)==WindowToolSet) {
        btnSet = new QToolButton(parent);
        btnSet->setObjectName("btnSet");
        btnSet->setAutoRaise(true);
        connect(btnSet,&QToolButton::clicked,this,&baseDialog::slotToolBtnSet);
        layout->addWidget(btnSet);
    }

    if ((flag & WindowToolMax)==WindowToolMax) {  qDebug()<<"btnMax";
        btnMax = new QToolButton(parent);
        btnMax->setObjectName("btnMax");
        btnMax->setAutoRaise(true);
        connect(btnMax,&QToolButton::clicked,this,&baseDialog::slotToolBtnMax);
        layout->addWidget(btnMax);
    }

    if ((flag & WindowToolNor)==WindowToolNor) {
        btnNor = new QToolButton(parent);
        btnNor->setObjectName("btnNor");
        btnNor->setAutoRaise(true);
        connect(btnNor,&QToolButton::clicked,this,&baseDialog::slotToolBtnNor);
        layout->addWidget(btnNor);
    }

    if ((flag & WindowToolMin)==WindowToolMin) {
        btnMin = new QToolButton(parent);
        btnMin->setObjectName("btnMin");
        btnMin->setAutoRaise(true);
        connect(btnMin,&QToolButton::clicked,this,&baseDialog::slotToolBtnMin);
        layout->addWidget(btnMin);
    }

    if ((flag & WindowToolClose)==WindowToolClose) {
        btnClose = new QToolButton(parent);
        btnClose->setObjectName("btnClose");
        btnClose->setAutoRaise(true);
        connect(btnClose,&QToolButton::clicked,this,&baseDialog::slotToolBtnClose);
        layout->addWidget(btnClose);
    }

    layout->setSpacing(0);
    layout->setContentsMargins(6,0,0,0);
    parent->setLayout(layout);
}

void baseDialog::resizeEvent(QResizeEvent *event)
{
    if (broudGroundPixmap && broudGroundWidget)
    {
        QPalette pal = broudGroundWidget->palette();
        pal.setBrush(QPalette::Window, QBrush(broudGroundPixmap->scaled(broudGroundWidget->size(),
                                                                        Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
        broudGroundWidget->setPalette(pal);
    }
    //设置圆角矩形
    QPainterPath path;
    path.addRoundedRect(rect(),5,5);
    setMask(QRegion(path.toFillPolygon().toPolygon()));
    return QDialog::resizeEvent(event);
}

void baseDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::LeftButton) {
        if (event->type()==QEvent::MouseButtonPress) {
            isPress = true;
            clickPos  = event->pos();   //qDebug()<<clickPos;
        }
    }
    QDialog::mousePressEvent(event);
}

void baseDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (!isPress) return ;
    move(event->globalPos() - clickPos);
    QDialog::mouseMoveEvent(event);
}

void baseDialog::mouseReleaseEvent(QMouseEvent *event)
{
    isPress = false;
}













