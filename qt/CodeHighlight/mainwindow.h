#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Syntax/syntaxhighlight.h"
#include "Editor/codeeditor.h"

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
};

#endif // MAINWINDOW_H
