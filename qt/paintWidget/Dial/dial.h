#ifndef DIAL_H
#define DIAL_H

#include <QDial>
#include <QMouseEvent>

class Dial : public QDial
{
    Q_OBJECT
public:
    explicit Dial(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    void UpdateAngle(QMouseEvent *event);

private:
    qreal pointRotate;
    bool mousePressed;
};

#endif // DIAL_H
