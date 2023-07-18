#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include "./route/route.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void resizeEvent(QResizeEvent* event);

private slots:
    void on_routeBtn_clicked();

private:
    Ui::Widget *ui;
    Route* routeWidget;
};

#endif // WIDGET_H
