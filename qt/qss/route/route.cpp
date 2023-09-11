#include "route.h"
#include "ui_route.h"
#include <QPropertyAnimation>
#include <QFont>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextCodec>

Route::Route(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Route),
    index(0)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
#endif
    QSqlDatabase sql = QSqlDatabase::addDatabase("QSQLITE", "lu");
    sql.setDatabaseName("Route.db");
    sql.setUserName("ldx");
    sql.setPassword("123");
    if (sql.open())
        qDebug() << "open succeed.";
    else
        qDebug() << "open error.";

    GetRouteItem("繁忙");
}

Route::~Route()
{
    delete ui;
}

void Route::AddButtons(QString name)
{
    CustomButton* button = new CustomButton(name, index++, this);
    ui->verticalLayout_4->addWidget(button);
    connect(button, SIGNAL(clicked(int)), this, SLOT(IndexButtonPressed(int)));
}

void Route::IndexButtonPressed(int index)
{
    qDebug() << "clicked" << index;
    hide();
}

void Route::on_backBtn_clicked()
{
    hide();
}

void ClearLayoutItem(QVBoxLayout* layout)
{
    // 清空Layout所有Item
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != NULL) {
        QWidget* widget = child->widget();
        if(widget) {
            widget->deleteLater();
        }
    }
}

void Route::GetRouteItem(QString type)
{
    // 根据type获取vip或免费路线
    QSqlDatabase sql = QSqlDatabase::database("lu");
    if (!sql.isOpen())
        return;

    index = 0;
    ClearLayoutItem(ui->verticalLayout_4);
    QSqlQuery query(sql);
    QString select = QString("select * from route where state = '%1'").arg(type);
    query.prepare(select);
    query.exec();
    while(query.next()) {
        AddButtons(query.value(0).toString());
    }
}

void Route::on_vipRouteBtn_clicked()
{
    ui->vipRouteBtn->setChecked(true);
    ui->freeRouteBtn->setChecked(false);

    // 获取vip路线
    GetRouteItem("良好");
}

void Route::on_freeRouteBtn_clicked()
{
    ui->vipRouteBtn->setChecked(false);
    ui->freeRouteBtn->setChecked(true);

    // 获取免费路线
    GetRouteItem("繁忙");
}
