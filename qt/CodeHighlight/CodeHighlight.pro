#-------------------------------------------------
#
# Project created by QtCreator 2023-05-24T15:32:10
#
#-------------------------------------------------

QT       += core gui svg xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CodeHighlight
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

include($$PWD/Syntax/Syntax.pri)
include($$PWD/Editor/Editor.pri)
include($$PWD/SvgView/SvgView.pri)
include($$PWD/Clock/Clock.pri)
