#ifndef ROUTE_H
#define ROUTE_H

#include <QWidget>
#include "custombutton.h"

namespace Ui {
class Route;
}

class Route : public QWidget
{
    Q_OBJECT

public:
    explicit Route(QWidget *parent = 0);
    ~Route();

    void AddButtons(QString name);

private slots:
    void IndexButtonPressed(int index);
    void GetRouteItem(QString type);
    void on_backBtn_clicked();

    void on_vipRouteBtn_clicked();

    void on_freeRouteBtn_clicked();

private:
    Ui::Route *ui;
    int index;
};

#endif // ROUTE_H
