#include "custombutton.h"

CustomButton::CustomButton(QString name, int index, QWidget *parent) :
    QPushButton(parent),
    mIndex(index)
{
    setText(name);
    QString objName = "item" + QString::number(index);
    setObjectName(objName);
    setMinimumHeight(35);
    QFont font(QString("Microsoft YaHei"));
    font.setPointSize(11);
    setFont(font);

    QString style = "CustomButton#" + objName + " {"
                    "background-color: rgb(78, 78, 78);"
                    "color: rgb(178, 178, 178);"
                    "border-radius: 5px; }"
                    "CustomButton#" + objName + ":hover {"
                    "background-color: rgb(58, 58, 58); }"
                    "CustomButton#" + objName + ":pressed {"
                    "background-color: rgb(48, 48, 48); }";
    setStyleSheet(style);
}

void CustomButton::mouseReleaseEvent(QMouseEvent */*event*/)
{
    emit clicked(mIndex);
}
