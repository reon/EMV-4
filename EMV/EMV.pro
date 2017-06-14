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
    QuakeML/quakemlreader.cpp \
    eventlayer.cpp \
    QuakeML/quakemlevent.cpp \
    Dialogs/fdsnrequestdialog.cpp \
    Dialogs/connectdialog.cpp

HEADERS  += emv.h \
        archcolors.h archpaintlayer.h mapwidget.h \
    QuakeML/quakemlreader.h \
    eventlayer.h \
    QuakeMl/quakemlevent.h \
    Dialogs/fdsnrequestdialog.h \
    Dialogs/connectdialog.h

FORMS    += emv.ui \
    Dialogs/fdsnrequestdialog.ui \
    Dialogs/connectdialog.ui

LIBS +=   -L/usr/local/lib -lmarblewidget-qt5

RESOURCES += \
    graphics.qrc
