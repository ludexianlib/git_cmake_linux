#ifndef SVGVIEW_H
#define SVGVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPaintEvent>

class SvgView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SvgView(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);

signals:

public slots:

};

#endif // SVGVIEW_H
