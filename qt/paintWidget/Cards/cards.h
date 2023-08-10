#ifndef CARDS_H
#define CARDS_H

#include <QWidget>

class Cards : public QWidget
{
    Q_OBJECT

public:
    explicit Cards(QWidget *parent = 0);

    void setTitle(const char *title);
    void setColorName(const char *purple, const char *green, const char *yellow);

protected:
    void paintEvent(QPaintEvent *event);

public slots:
        void setValue(int purpleVal, int greenVal, int yellowVal);

private:
    const char *title;
    const char *purpleName;
    const char *greenName;
    const char *yellowName;
    int purpleValue, greenValue, yellowValue;

signals:

public slots:

};

#endif // CARDS_H
