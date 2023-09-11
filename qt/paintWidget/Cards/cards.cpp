#include "cards.h"
#include <QPainter>
#include <QDebug>
#include <QTextCodec>

Cards::Cards(QWidget *parent) :
    QWidget(parent),
    title("标题"),
    purpleName("描述1"),
    greenName("描述2"),
    yellowName("描述3"),
    purpleValue(360),
    greenValue(245),
    yellowValue(190)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
}

void Cards::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int x = width() / 2, y = height() / 2;
    int min = qMin(x, y);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
//    painter.translate(x, y);

    painter.setPen(Qt::NoPen);

    // 外部矩形
    painter.setBrush(QColor(86, 92, 106));
    painter.drawRoundedRect(min * 0.1, min * 0.1, min * 1.8, min * 1.8, min * 0.1, min * 0.1);

    // 标题
    painter.setPen(QColor(238, 238, 238));
    QFont font("STXingkai", min * 0.1);
    painter.setFont(font);
    painter.drawText(min * 0.2, min * 0.15, min * 0.6, min * 0.4, Qt::AlignCenter, title);

    // 颜色点
    float scale1, scale2, scale3, scale4;
    painter.save();

    scale1 = min * 0.4;
    scale2 = min * 0.6;
    scale3 = min * 0.02;
    scale4 = min * 0.5;

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(85, 82, 216)); // 紫
    painter.drawEllipse(QPointF(scale1, scale2), scale3, scale3);
    painter.translate(scale4, 0);
    painter.setBrush(QColor(28, 190, 151)); // 绿
    painter.drawEllipse(QPointF(scale1, scale2), scale3, scale3);
    painter.translate(scale4, 0);
    painter.setBrush(QColor(240, 180, 10)); // 黄
    painter.drawEllipse(QPointF(scale1, scale2), scale3, scale3);
    painter.restore();

    // 描述
    painter.save();
     painter.setPen(QColor(158, 158, 158));
    font = QFont("STXingkai", min * 0.08);
    painter.setFont(font);

    scale1 = min * 0.42;
    scale2 = min * 0.5;
    scale3 = min * 0.4;
    scale4 = min * 0.2;

    painter.drawText(scale1, scale2,scale3, scale4, Qt::AlignCenter, QString::fromUtf8(purpleName));
    painter.translate(scale2, 0);
    painter.drawText(scale1, scale2,scale3, scale4, Qt::AlignCenter, QString::fromUtf8(greenName));
    painter.translate(scale2, 0);
    painter.drawText(scale1, scale2,scale3, scale4, Qt::AlignCenter, QString::fromUtf8(yellowName));
    painter.translate(scale2, 0);
    painter.restore();

    // 圆圈
    QPen pen(QColor(158, 158, 158));
    pen.setWidth(min * 0.03);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);

    // 黑底圆
    painter.drawEllipse(min * 0.5, min * 0.75, min, min);
    painter.drawEllipse(min * 0.6, min * 0.85, min * 0.8, min * 0.8);
    painter.drawEllipse(min * 0.7, min * 0.95, min * 0.6, min * 0.6);

    // 紫色圆
    painter.save();
    pen = QPen(QColor(85, 82, 216));
    pen.setWidth(min * 0.03);
    painter.setPen(pen);
    painter.drawArc(min * 0.5, min * 0.75, min, min, 90 * 16, -purpleValue * 16);
    painter.restore();
    // 绿色圆
    pen = QPen(QColor(28, 190, 151));
    pen.setWidth(min * 0.03);
    painter.setPen(pen);
    painter.drawArc(min * 0.6, min * 0.85, min * 0.8, min * 0.8, 90 * 16, -greenValue * 16);
    // 黄色圆
    pen = QPen(QColor(240, 180, 10));
    pen.setWidth(min * 0.03);
    painter.setPen(pen);
    painter.drawArc(min * 0.7, min * 0.95, min * 0.6, min * 0.6, 90 * 16, -yellowValue * 16);
}

void Cards::setValue(int purpleVal, int greenVal, int yellowVal)
{
    if (purpleVal > 360)
        purpleVal = 360;
    if (purpleVal < 0)
        purpleVal = 0;

    if (greenVal > 360)
        greenVal = 360;
    if (greenVal < 0)
        greenVal = 0;

    if (yellowVal > 360)
        yellowVal = 360;
    if (yellowVal < 0)
        yellowVal = 0;

    purpleValue = purpleVal;
    greenValue = greenVal;
    yellowValue = yellowVal;
    update();
}

void Cards::setTitle(const char *title)
{
    this->title = title;
    update();
}

void Cards::setColorName(const char *purple, const char *green, const char *yellow)
{
    purpleName = purple;
    greenName = green;
    yellowName = yellow;
    update();
}
