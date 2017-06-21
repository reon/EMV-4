#-------------------------------------------------
#
# Project created by QtCreator 2017-06-09T12:30:35
#
#-------------------------------------------------
# message($$QMAKESPEC)

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EMV
TEMPLATE = app

CONFIG += c++11

#For promoting widget in emv.ui
INCLUDEPATH += Widgets/

SOURCES += main.cpp\
        emv.cpp \
        mapwidget.cpp archpaintlayer.cpp \
    QuakeML/quakemlreader.cpp \
    eventlayer.cpp \
    QuakeML/quakemlevent.cpp \
    Dialogs/fdsnrequestdialog.cpp \
    Dialogs/connectdialog.cpp \
    Widgets/quakemltable.cpp

HEADERS  += emv.h \
        archcolors.h archpaintlayer.h mapwidget.h \
    QuakeML/quakemlreader.h \
    eventlayer.h \
    QuakeML/quakemlevent.h \
    Dialogs/fdsnrequestdialog.h \
    Dialogs/connectdialog.h \
    Widgets/quakemltable.h

FORMS    += emv.ui \
    Dialogs/fdsnrequestdialog.ui \
    Dialogs/connectdialog.ui

LIBS +=   -L/usr/local/lib -lmarblewidget-qt5

RESOURCES += \
    graphics.qrc


# ---- EarthWorm Injection ----

linux-g++:DEFINES += _LINUX
linux-g++-64:DEFINES += _LINUX

SOURCES += EarthWorm/src/data_exchange/import_generic/import_generic.c \
    EarthWorm/src/libsrc/unix/socket_ew.c \
    EarthWorm/src/libsrc/util/socket_ew_common.c \
    EarthWormComp.cpp \
    EarthWormHacks.cpp

HEADERS += EarthWormComp.h \
    EarthWormHacks.h

INCLUDEPATH += EarthWorm/include

LIBS += -L$$_PRO_FILE_PWD_/EarthWorm/lib -lew -lew_mt

DISTFILES += \
    Notes.txt
