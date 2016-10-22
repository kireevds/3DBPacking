#-------------------------------------------------
#
# Project created by QtCreator 2016-10-15T02:48:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DBPacking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    container.cpp \
    object.cpp \
    sortingalg.cpp

HEADERS  += mainwindow.h \
    container.h \
    object.h \
    sortingalg.h

FORMS    += mainwindow.ui
