#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CustomButton(QString name, int index, QWidget *parent = 0);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked(int);

public slots:

private:
    int mIndex;

};

#endif // CUSTOMBUTTON_H
