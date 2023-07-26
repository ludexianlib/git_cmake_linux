#include "widget.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // setStyleSheet
    QFile file(":/res/style.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    Widget w;
    w.show();

    return a.exec();
}
