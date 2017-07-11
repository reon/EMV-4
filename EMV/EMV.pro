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

macx {
    DEFINES += NO_EARTHWORM
    INCLUDEPATH += /Users/alexm/lib/include/
}

SOURCES += main.cpp\
        emv.cpp \
    mapwidget.cpp \
    MarbleLayers/archpaintlayer.cpp \
    MarbleLayers/eventlayer.cpp \
    QuakeML/quakemlreader.cpp \
    QuakeML/quakemlevent.cpp \
    Dialogs/fdsnrequestdialog.cpp \
    Dialogs/connectdialog.cpp \
    Widgets/quakemltable.cpp \
    EWC/teststring.cpp \
    EWC/earthwormsite.cpp \
    EWC/hypomessage.cpp \
    emv_slots.cpp \
    Dialogs/earthwormsettings.cpp

HEADERS  += emv.h \
    mapwidget.h \
    MarbleLayers/archcolors.h \
    MarbleLayers/archpaintlayer.h \
    MarbleLayers/eventlayer.h \
    QuakeML/quakemlreader.h \
    QuakeML/quakemlevent.h \
    Dialogs/fdsnrequestdialog.h \
    Dialogs/connectdialog.h \
    Widgets/quakemltable.h \
    EWC/teststring.h \
    EWC/earthwormsite.h \
    EWC/hypomessage.h \
    EWC/importgenericconfig.h \
    Dialogs/earthwormsettings.h

FORMS    += emv.ui \
    Dialogs/fdsnrequestdialog.ui \
    Dialogs/connectdialog.ui \
    Dialogs/earthwormsettings.ui

macx {
    LIBS += -L/Users/alexm/lib/ -lmarblewidget-qt5.0.27.1
}

unix:!macx {
    LIBS +=   -L/usr/local/lib -lmarblewidget-qt5
}

RESOURCES += \
    Embedded/emvresources.qrc


# ---- EarthWorm Injection ----

unix:!macx {

linux-g++:DEFINES += _LINUX
linux-g++-64:DEFINES += _LINUX

SOURCES += EarthWorm/src/data_exchange/import_generic/import_generic.c \
    EarthWorm/src/libsrc/unix/socket_ew.c \
    EarthWorm/src/libsrc/util/socket_ew_common.c \
#    EarthWorm/src/libsrc/util/read_arc.c \
    EWC/EarthWormComp.cpp \
    EWC/EarthWormHacks.cpp

HEADERS += EWC/EarthWormComp.h \
    EWC/EarthWormHacks.h

INCLUDEPATH += EarthWorm/include

LIBS += -L$$_PRO_FILE_PWD_/EarthWorm/lib -lew -lew_mt

}

DISTFILES += \
    Notes.txt \
    Embedded/Files/StationList.txt \
    Embedded/Files/StationList2.txt \
    import_generic.d




