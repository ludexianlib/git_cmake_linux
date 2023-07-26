#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>
#include "./Clock/clock.h"
#include "./Dial/dial.h"
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    int i = 0;
    QButtonGroup* group = new QButtonGroup(this);
    group->addButton(ui->widgetBtn, i++);
    group->addButton(ui->dialBtn, i++);
    group->addButton(ui->progressBtn, i++);
    connect(group, SIGNAL(buttonClicked(int)), ui->stackedWidget, SLOT(setCurrentIndex(int)));

    Clock* clock = new Clock(this);
    ui->widgetLayout->addWidget(clock, 0, 0);

    Dial* dial = new Dial(this);
    ui->dialLayout->addWidget(dial, 0, 0);
}

Widget::~Widget()
{
    delete ui;
}
