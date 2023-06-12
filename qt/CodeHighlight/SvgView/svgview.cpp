#include "svgview.h"
#include <QFile>
#include <QDebug>
#include <qmath.h>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsSvgItem>

SvgView::SvgView(QWidget *parent) :
    QGraphicsView(parent)
{
    // 设置View场景、拖动方法、刷新方法
    setScene(new QGraphicsScene(this));
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(ScrollHandDrag);
    setViewportUpdateMode(FullViewportUpdate);

    // 加载svg文件
    QGraphicsScene* s = scene();
    s->clear();
    resetTransform();
    QGraphicsSvgItem* svgItem = new QGraphicsSvgItem("://svg/test.svg");
    svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
    svgItem->setCacheMode(QGraphicsItem::NoCache);
    svgItem->setZValue(0);
    s->addItem(svgItem);
}

void SvgView::paintEvent(QPaintEvent *event)
{
    // 绘图事件
    QGraphicsView::paintEvent(event);
}

void SvgView::wheelEvent(QWheelEvent *event)
{
    // 滚轮缩放事件
    qreal factor = qPow(1.2, event->delta() / 240.0);
    scale(factor, factor);
    event->accept();
}
