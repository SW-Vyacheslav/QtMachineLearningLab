#-------------------------------------------------
#
# Project created by QtCreator 2019-09-19T20:14:57
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMachineLearningLab
TEMPLATE = app


SOURCES += main.cpp\
    dataclass.cpp \
    datafeature.cpp \
    datamodel.cpp \
        mainwindow.cpp \
    dataholder.cpp \
    paintwidget.cpp

HEADERS  += mainwindow.h \
    dataclass.h \
    datafeature.h \
    dataholder.h \
    datamodel.h \
    paintwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    data.csv
