#-------------------------------------------------
#
# Project created by QtCreator 2023-07-06T10:42:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paintWidget
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui

include($$PWD/Clock/Clock.pri)
include($$PWD/Dial/Dial.pri)
include($$PWD/ProgressBar/ProgressBar.pri)
include($$PWD/Cards/Cards.pri)

RESOURCES += \
    res.qrc
