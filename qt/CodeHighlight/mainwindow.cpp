#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <QTextStream>
#include "SvgView/svgview.h"
#include "Clock/clock.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    setWindowOpacity(0.5); // 窗口透明度
//    setWindowFlags(Qt::WindowStaysOnTopHint); // 顶层窗口

    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

    // 创建高亮对象
    syntaxHighlight = new SyntaxHighlight(ui->plainTextEdit->document());

    // 连接文件操作QAction
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(OpenFile()));

    // svg view
    SvgView* svgView = new SvgView(this);
    ui->horizontalLayout_2->addWidget(svgView);

    // clock
    Clock* clock = new Clock(this);
    ui->horizontalLayout->addWidget(clock, 1);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete syntaxHighlight;
}

void MainWindow::OpenFile()
{
    QFile file("nc.txt");
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    QString str = in.readAll();
    ui->plainTextEdit->setPlainText(str);
    file.close();
}
