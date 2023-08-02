#include "progressbar.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QRadialGradient>

ProgressBar::ProgressBar(QWidget *parent) :
    QWidget(parent), mValue(50)
{
}

void ProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int x = width() / 2, y = height() / 2;
    int min = qMin(x, y);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(x, y);

    // 刻度
    painter.save();
    painter.setPen(Qt::NoPen);

    for (int i = 0; i < 100; i++) {
        if (i <= mValue)
            painter.setBrush(QColor(208, 208, 208));
        else
            painter.setBrush(QColor(178, 178, 178));

        if (i == mValue)
            painter.drawRect(0, -min*0.9, min*0.02, min*0.2);
        else
            painter.drawRect(0, -min*0.9, min*0.02, min*0.1);

        painter.rotate(3.6);
    }
    painter.restore();

    // 数值
    QFont font;
    QPen pen;
    pen.setColor(QColor(208, 208, 208));
    font.setFamily("Microsoft YaHei");
    font.setPointSize(min / 4);
    painter.setFont(font);
    painter.setPen(pen);
    QString value = QString("%1%").arg(mValue);
    painter.drawText(-min * 0.45, -min * 0.2, min * 0.9, min * 0.4, Qt::AlignCenter, value);
}

void ProgressBar::setValue(int value)
{
    if (value > 100)
        value = 100;

    if (value < 0)
        value = 0;

    mValue = value;
    update();
}
