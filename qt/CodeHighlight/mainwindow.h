#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Syntax/syntaxhighlight.h"
#include "Editor/codeeditor.h"
#include "SvgView/svgview.h"
#include "Clock/clock.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void OpenFile();

private:
    Ui::MainWindow *ui;
    SyntaxHighlight* syntaxHighlight;
    SvgView* svgView;
    Clock* clock;
};

#endif // MAINWINDOW_H
