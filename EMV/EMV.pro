#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T12:30:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EMV
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        emv.cpp \
        mapwidget.cpp archpaintlayer.cpp \
    quakemlreader.cpp \
    eventlayer.cpp \
    quakemlevent.cpp \
    fdsnrequestdialog.cpp

HEADERS  += emv.h \
        archcolors.h archpaintlayer.h mapwidget.h \
    quakemlreader.h \
    eventlayer.h \
    quakemlevent.h \
    fdsnrequestdialog.h

FORMS    += emv.ui \
    fdsnrequestdialog.ui

LIBS +=   -L/usr/local/lib -lmarblewidget-qt5

RESOURCES += \
    graphics.qrc
