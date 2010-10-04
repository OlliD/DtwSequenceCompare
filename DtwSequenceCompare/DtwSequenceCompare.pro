#-------------------------------------------------
#
# Project created by QtCreator 2010-09-28T15:09:09
#
#-------------------------------------------------

QT       += core gui

TARGET = DtwSequenceCompare
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    logger.cpp \
    iisutracker.cpp \
    gesturewindow.cpp \
    filetracker.cpp \
    dtwcontroller.cpp \
    dtw.cpp \
    dataholder.cpp \
    plotwidget.cpp

HEADERS  += mainwindow.h \
    logger.h \
    iisutracker.h \
    gesturewindow.h \
    filetracker.h \
    dtwcontroller.h \
    dtw.h \
    dataholder.h \
    plotwidget.h

FORMS    += mainwindow.ui

LIBS += -L/Users/odamm/Dropbox/DtwSequenceCompare/qwt-5.2.1/lib/ -lqwt
