#include "linesignatrue.h"
#include <QLabel>
#include <QDebug>
#include <QFocusEvent>

lineSignatrue::lineSignatrue(QWidget *parent):QLineEdit(parent)
{
    rightLabel=NULL;
    labelPath="";
    setAttribute(Qt::WA_TranslucentBackground);
}

lineSignatrue::lineSignatrue(const QString &contents, QWidget *parent):QLineEdit(contents,parent)
{
    rightLabel=NULL;
    labelPath="";
    setAttribute(Qt::WA_TranslucentBackground);
}

lineSignatrue::lineSignatrue(const QString &contents, const QString &pic, QWidget *parent):QLineEdit(contents,parent)
{
    rightLabel=NULL;
    labelPath=pic;
    setAttribute(Qt::WA_TranslucentBackground);
}

lineSignatrue::~lineSignatrue()
{
    delete rightLabel;
    rightLabel=NULL;
}

void lineSignatrue::setLablePic(const QString &path)
{
    labelPath = path;
    init();
}

void lineSignatrue::setLineStyle(QString style)
{
    setStyleSheet(style);
}

void lineSignatrue::init()
{
    if (rightLabel==NULL) {
        rightLabel = new QLabel(this);
        rightLabel->setScaledContents(true);
        rightLabel->setCursor(QCursor(Qt::ArrowCursor));
    }
    changeLabelPosition();
}

void lineSignatrue::changeLabelPosition()
{
    if (rightLabel==NULL) return ;
    if (labelPath.isEmpty()) {
        rightLabel->hide();
    }
    else {
        int labelWidth = height()-2;
        int labelHight =  height()-2;
        rightLabel->setPixmap(QPixmap(labelPath));
        rightLabel->setMaximumSize(labelWidth,labelHight);
        rightLabel->setGeometry(   width()-labelWidth-2,(height()-labelHight)/2,labelWidth,labelHight );
        setTextMargins(1,0,labelWidth,0);
        rightLabel->hide();
    }
}

void lineSignatrue::focusInEvent(QFocusEvent *e)
{
    if (rightLabel) rightLabel->show();
    QLineEdit::focusInEvent(e);
}

void lineSignatrue::focusOutEvent(QFocusEvent *e)
{
    if (rightLabel) rightLabel->hide();
    QLineEdit::focusOutEvent(e);
}





