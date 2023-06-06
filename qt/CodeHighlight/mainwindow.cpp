#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建高亮对象
    syntaxHighlight = new SyntaxHighlight(ui->plainTextEdit->document());

    // 连接文件操作QAction
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenFile()));

    // svg view
    svgView = new SvgView(this);
    ui->horizontalLayout_2->addWidget(svgView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete syntaxHighlight;
}

void MainWindow::OpenFile()
{
    QFile file("nc.txt");
    file.open(QFile::ReadOnly);
    char buf[128];
    QString str;
    while (!file.atEnd()) {
        memset(buf, 0, 128);
        file.read(buf, 127);
        str.append(buf);
    }
    ui->plainTextEdit->setPlainText(str);
    file.close();
}
