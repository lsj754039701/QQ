#ifndef LINESIGNATRUE_H
#define LINESIGNATRUE_H
#include <QLineEdit>
class QLabel;

class lineSignatrue : public QLineEdit
{
    Q_OBJECT
public:
    explicit lineSignatrue(QWidget *parent=0);
    explicit lineSignatrue(const QString& contents, QWidget * parent = 0);
    explicit lineSignatrue(const QString& contents, const QString& pic,QWidget *parent=0);
    ~lineSignatrue();

    void setLablePic(const QString& path);
    void setLineStyle(QString style);

protected:
    void init();
    void changeLabelPosition();
    void focusInEvent(QFocusEvent * e);
    void	focusOutEvent(QFocusEvent * e);

private:
    QLabel *rightLabel;
    QString labelPath;
};

#endif // LINESIGNATRUE_H
