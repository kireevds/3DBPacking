#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T02:48:05
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
    sortingalg.cpp \
    resultwindow.cpp \
    continfowindow.cpp

HEADERS  += mainwindow.h \
    container.h \
    object.h \
    sortingalg.h \
    resultwindow.h \
    continfowindow.h

FORMS    += mainwindow.ui \
    resultwindow.ui \
    continfowindow.ui
