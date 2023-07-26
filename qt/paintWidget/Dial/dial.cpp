#include "dial.h"
#include <QPainter>
#include <QDebug>
#include <QPainterPath>
#include <qmath.h>

#define PI 3.1415926

Dial::Dial(QWidget *parent) :
    QDial(parent),
    pointRotate(0)
{

}

void Dial::paintEvent(QPaintEvent */*event*/)
{
    int x = width() / 2, y = height() / 2;
    int min = qMin(x, y);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(x, y);

    painter.setPen(Qt::NoPen);

    // 刻度
    painter.save();
    painter.rotate(-135);
    double reflectAngle = pointRotate + 135.0; // 将当前角度映射到（0 - 270）范围
    for (int i = 0; i < 21; i++) {
        if (i < (int)(reflectAngle / 13.5) + 1) { // 计算当前角度画出进度条白点
            if (reflectAngle < 2)
                painter.setBrush(QColor(65, 65, 65));
            else
                painter.setBrush(QColor(255, 255, 255));
        }
        else {
            painter.setBrush(QColor(65, 65, 65));
        }

        if (i % 5 == 0)
            painter.drawEllipse(QPointF(0, -min*0.9), min*0.05, min*0.05);
        else
            painter.drawEllipse(QPointF(0, -min*0.9), min*0.03, min*0.03);
        painter.rotate(13.5);
    }
    painter.restore();


    // 外圆
    QRadialGradient rGradient(0, 0, min, -min*0.6, -min*0.6);
    rGradient.setColorAt(0, QColor(255, 255, 255));
    rGradient.setColorAt(1, QColor(195, 195, 195));
    painter.setBrush(QBrush(rGradient));
    painter.drawEllipse(QPointF(0, 0), min*0.8, min*0.8);

    // 内圆
    painter.setBrush(QBrush(QColor(105, 105, 105)));
    painter.drawEllipse(QPointF(0, 0), min*0.7, min*0.7);

    // 最内圆旋钮
    QConicalGradient cGradient(QPoint(0, 0), 360);
    cGradient.setColorAt(0, Qt::white);
    cGradient.setColorAt(0.15, QColor(200, 200, 200));
    cGradient.setColorAt(0.25, QColor(200, 200, 200));
    cGradient.setColorAt(0.38, Qt::white);
    cGradient.setColorAt(0.65, QColor(200, 200, 200));
    cGradient.setColorAt(0.75, Qt::white);
    cGradient.setColorAt(0.83, QColor(200, 200, 200));
    cGradient.setColorAt(1, Qt::white);
    painter.setBrush(cGradient);
    painter.drawEllipse(QPointF(0, 0), min*0.65, min*0.65);

    // 旋钮点
    painter.save();
    painter.setBrush(QColor(65, 65, 65));
    painter.rotate(pointRotate);
    painter.drawEllipse(QPointF(0, -min*0.55), min*0.04, min*0.04);
    painter.restore();
}

void Dial::mousePressEvent(QMouseEvent *event)
{
    mousePressed = true;
    UpdateAngle(event);
}

void Dial::mouseReleaseEvent(QMouseEvent */*event*/)
{
    mousePressed = false;
}

void Dial::mouseMoveEvent(QMouseEvent *event)
{
    if (mousePressed) {
        UpdateAngle(event);
    }
}

inline void Dial::UpdateAngle(QMouseEvent *event)
{
    double dy = (double)height() / 2 - event->pos().y();
    double dx = (double)event->pos().x() - width() / 2;
    if ((1.1*dx > dy) && (-1.1*dx > dy)) // 下方无效区域：y < 1.1*x && y < -1.1*x
        return;

    double a = (dx || dy) ? qAtan2(dy, dx) : 0;
    if (a < PI / -2)
        a = a + PI * 2;
    double angle = 180 / PI * a;
    pointRotate = -angle + 90.0; // 将圆心坐标映射到QPainter绘图坐标
    update();
}
