#-------------------------------------------------
#
# Project created by QtCreator 2015-10-15T02:48:05
#
#-------------------------------------------------

QT += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DBPacking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    container.cpp \
    object.cpp \
    sortingalg.cpp \
    result.cpp \
    continfo.cpp \
    mainscene.cpp

HEADERS  += mainwindow.h \
    container.h \
    object.h \
    sortingalg.h \
    result.h \
    continfo.h \
    datasend.h \
    mainscene.h

FORMS    += mainwindow.ui \
    result.ui \
    continfo.ui
