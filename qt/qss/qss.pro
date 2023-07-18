#-------------------------------------------------
#
# Project created by QtCreator 2023-06-26T11:58:02
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qss
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

RESOURCES += \
    res.qrc

include($$PWD/route/route.pri)
