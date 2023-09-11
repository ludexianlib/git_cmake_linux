#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QDebug>
#include <QStackedWidget>
#include <QHash>
#include <QTimer>
#include "./Clock/clock.h"
#include "./Dial/dial.h"
#include "./ProgressBar/ProgressBar.h"
#include "./Cards/Cards.h"

static QHash<QString, QWidget*> widgetMap;

#define REGISTER_CLASS(name)                               \
class Register##name {                                                  \
    public:                                                                       \
        Register##name() {                                                \
            widgetMap[#name] = new name();                      \
        }                                                                           \
    };                                                                              \
 Register##name register##name;

#define DESTORY_CLASS                                               \
QHashIterator<QString, QWidget*> it(widgetMap);             \
while (it.hasNext()) {                                                           \
    it.next();                                                                         \
    delete it.value();                                                             \
}


QWidget* getRegisterWidget(QString name)
{
    QWidget *widget = widgetMap[name];
    return widget;
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    REGISTER_CLASS(Clock);
    REGISTER_CLASS(Dial);
    REGISTER_CLASS(ProgressBar);
    REGISTER_CLASS(Cards);

    ui->setupUi(this);

    QFile file("://res/page.txt");
    file.open(QFile::ReadOnly);
    QStringList textList;

    while (!file.atEnd()) {
        QString str = file.readLine().trimmed();
        textList << str;
    }

    QButtonGroup *group = new QButtonGroup(this);
    QStackedWidget *stackedWidget = new QStackedWidget(this);

    for (int i = 0; i < textList.size(); i++) {
        // 添加widget
        QWidget *widget = getRegisterWidget(textList.at(i));
        if (widget == NULL)
            continue;
        stackedWidget->addWidget(widget);

        // 设置button
        QPushButton *button = new QPushButton(this);
        button->setMinimumSize(135, 35);
        QFont font = button->font();
        font.setPointSize(15);
        button->setFont(font);
        button->setText(textList.at(i));
        ui->verticalLayout->addWidget(button);

        group->addButton(button, i);
    }

    connect(group, SIGNAL(buttonClicked(int)), stackedWidget, SLOT(setCurrentIndex(int)));

    ui->verticalLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    ui->verticalLayout_2->addWidget(stackedWidget);
}

Widget::~Widget()
{
    delete ui;
    DESTORY_CLASS;
}
