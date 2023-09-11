#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include <QWidget>
#include <QTimer>
#include <QShowEvent>

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    explicit ProgressBar(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

signals:

public slots:
    void setValue(int value);
    void setValue();

private:
    int mValue;
    QTimer *timer;

};

#endif // PROGRESSBAR_H
