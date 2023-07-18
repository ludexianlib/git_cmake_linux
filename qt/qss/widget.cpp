#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QPropertyAnimation>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    routeWidget = new Route(this);
    routeWidget->hide();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event);
    routeWidget->resize(width() / 4, height());
    routeWidget->move(width() - routeWidget->width(), 0);
}

void Widget::on_routeBtn_clicked()
{
    if (!routeWidget->isHidden())
        return;

    routeWidget->show();
    routeWidget->move(width(), 0);
    QPropertyAnimation* animation = new QPropertyAnimation(routeWidget, "pos");
    animation->setDuration(200);
    animation->setStartValue(QPoint(width(), 0));
    animation->setEndValue(QPoint(width() - routeWidget->width(), 0));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
