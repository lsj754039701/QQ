#include "titlewidget.h"
#include <QFont>
#include <QHBoxLayout>
#include <QPalette>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>

static const int TITLE_HEIGHT = 30;
static const int FRAME_BORDER = 2;

titleWidget::titleWidget(QWidget *parent,QString title):QWidget(parent)
{
    closeBtn = new QToolButton;
    restoreBtn = new QToolButton;
    minBtn = new QToolButton;
    maxBtn = new QToolButton;
    setBtn = new QToolButton;
    logoLab = new QLabel;
    titleLab = new QLabel;
    height  =110;

    isMax = false;
    isPress = false;

    closeBtn->setIcon(QPixmap(":/login/image/systembutton/btn_close_highlight.png"));
    restoreBtn->setIcon(QPixmap(":/login/image/systembutton/btn_restore_down.png"));
    minBtn->setIcon(QPixmap(":/login/image/systembutton/btn_mini_highlight.png"));
    maxBtn->setIcon(QPixmap(":/login/image/systembutton/btn_max_highlight.png"));
    setBtn->setIcon(QPixmap(":/login/image/systembutton/btn_set_normal.png"));

    QSize iconSize(25,25);

    logoLab->setPixmap(QPixmap(":/login/image/menu_btn_highlight.png"));
    logoLab->setFixedSize(iconSize);
    logoLab->setScaledContents(true);

    titleLab->setText(title);
    QFont font = titleLab->font();
    //font.setBold(true);
    font.setPointSize(15);
    //font.setItalic(true);
    titleLab->setFont(font);
    titleLab->setObjectName("whiteLab");

    closeBtn->setToolTip("关闭");
    closeBtn->setIconSize(iconSize);
    closeBtn->setFixedSize(iconSize);
    closeBtn->setStyleSheet("border-radius:2px;border:1px solid rgb(180, 180, 180);");
    closeBtn->setAutoRaise(true);

    maxBtn->setToolTip("最大化");
    maxBtn->setIconSize(iconSize);
    maxBtn->setFixedSize(iconSize);
    maxBtn->setStyleSheet("border-radius:2px;border:1px solid rgb(180, 180, 180);");
    maxBtn->setAutoRaise(true);
    maxBtn->setVisible(false);

    minBtn->setToolTip("最小化 ");
    minBtn->setIconSize(iconSize);
    minBtn->setFixedSize(iconSize);
    minBtn->setStyleSheet("border-radius:2px;border:1px solid rgb(180, 180, 180);");

    restoreBtn->setToolTip("还原");
    restoreBtn->setIconSize(iconSize);
    restoreBtn->setFixedSize(iconSize);
   // restoreBtn->setStyleSheet("border-radius:2px;border:1px solid rgb(180, 180, 180);");

    setBtn->setToolTip("选项");
    setBtn->setIconSize(iconSize);
    setBtn->setFixedSize(iconSize);
    setBtn->setStyleSheet("border-radius:2px;border:1px solid rgb(180, 180, 180);");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(logoLab,0,Qt::AlignTop);
    layout->addWidget(titleLab,0,Qt::AlignTop);
    layout->addStretch();

    layout->addWidget(setBtn,0,Qt::AlignTop);
    layout->addWidget(minBtn,0,Qt::AlignTop);
    layout->addWidget(maxBtn,0,Qt::AlignTop);
    layout->addWidget(closeBtn,0,Qt::AlignTop);

    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setFixedHeight(height);
    setLayout(layout);
    setAutoFillBackground(true);

    //用palette设置背景图片
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,QPixmap(":/login/image/noon.png").scaled(size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
    setPalette(pal);

    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMouseTracking(true);

    connect(closeBtn,&QToolButton::clicked,this,&titleWidget::slotCloseWidget);
}

void titleWidget::slotCloseWidget()
{
    emit closeWidget();
}

void titleWidget::mousePressEvent(QMouseEvent *e)
{
    startPos = e->globalPos();
    clickPos = e->pos();

    if (e->button() == Qt::LeftButton) {
        if (e->type() == QEvent::MouseButtonPress)
            isPress = true;
        else if (e->type() == QEvent::MouseButtonDblClick && e->pos().y() <= TITLE_HEIGHT)
            emit showMaxRestored();
    }
}

void titleWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (isMax || !isPress) return;
    emit moveWidget(e->globalPos()  - clickPos);
}

void titleWidget::mouseReleaseEvent(QMouseEvent *e)
{
    isPress = false;
}

bool titleWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType);


}

void titleWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
}


















