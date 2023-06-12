#include "clock.h"
#include <QtGui>

Clock::Clock(QWidget *parent) :
    QWidget(parent)
{

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(500);
}

void Clock::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)

    QTime time = QTime::currentTime();

    int x = width() / 2, y = height() / 2;
    int min = qMin(x, y);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(x, y);

    // 外圆
    painter.setPen(Qt::NoPen);
    QLinearGradient lGradient(QPointF(0, -min), QPointF(0, min));
    lGradient.setColorAt(0.05, QColor(225, 225, 225));
    lGradient.setColorAt(0.45, QColor(150, 150, 150));
    lGradient.setColorAt(0.55, QColor(150, 150, 150));
    lGradient.setColorAt(1, QColor(225, 225, 225));
    painter.setBrush(QBrush(lGradient));
    painter.drawEllipse(QPointF(0, 0), min, min);

    // 内圆
    QRadialGradient rGradient(0, 0, min*0.8, 0, -0.5*min);
    rGradient.setColorAt(0.2, QColor(185, 185, 185));
    rGradient.setColorAt(1, QColor(65, 65, 65));
    painter.setBrush(QBrush(rGradient));
    painter.drawEllipse(QPointF(0, 0), min*0.8, min*0.8);

    // 刻度
    painter.save();
    painter.setBrush(Qt::white);
    for (int i = 0; i < 12; i++) {
        painter.drawEllipse(QPointF(0, -min*0.7), min*0.03, min*0.03);
        painter.rotate(30);
    }
    painter.restore();

    // 时针
    painter.save();
    painter.setBrush(QColor(255, 255, 255, 225));
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawRoundedRect(QRectF(-min*0.035, -min*0.67, min*0.07, min*0.67), min*0.2, min*0.04);
    painter.restore();

    // 分针
    painter.save();
    painter.setBrush(QColor(255, 255, 255, 225));
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawRoundedRect(QRectF(-min*0.025, -min*0.85, min*0.05, min*0.85), min*0.2, min*0.03);
    painter.restore();

    // 秒针
    painter.save();
    painter.setBrush(QColor(255, 0, 0));
    painter.rotate(6 * time.second());
    painter.drawRoundedRect(QRectF(-min*0.007, -min*0.85, min*0.014, min*0.85), 0, 0);
    painter.restore();

    painter.setBrush(QColor(255, 255, 255));
    painter.drawEllipse(QPointF(0, 0), min*0.06, min*0.06);
}

