#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include <QObject>

class titleWidget:public QWidget
{
    Q_OBJECT
public:
    titleWidget(QWidget *parent=0,QString title="");

public slots:
    void slotCloseWidget();

signals:
    void showSmall();
    void showMaxRestored();
    void moveWidget(QPoint);
    bool closeWidget();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void paintEvent(QPaintEvent *e);

private:
    QToolButton *closeBtn,*restoreBtn,*minBtn,*maxBtn,*setBtn;
    QLabel *logoLab,*titleLab;
    int height;

    bool isMax;
    bool isPress;
    QPoint startPos;
    QPoint clickPos;
};

#endif // TITLEWIDGET_H
