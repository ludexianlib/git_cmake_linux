#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPaintEvent>

class Clock : public QWidget
{
    Q_OBJECT
public:
    explicit Clock(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CLOCK_H
