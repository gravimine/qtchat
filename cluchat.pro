#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T16:56:23
#
#-------------------------------------------------
QT       += core gui network
#QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(ACore/ACore.pri)
include(ANetwork/ANetwork.pri)
TARGET = CluChat
TEMPLATE = app
INCLUDEPATH += ./include
SOURCES += src/main.cpp\
           src/mainwindow.cpp \
           src/ui.cpp \
           src/achat.cpp

HEADERS  += include/mainwindow.h \
    include/dialog.h \
    include/registr.h \
    include/form.h \
    include/kabinet.h \
    include/auimanager.h \
    include/loading.h \
    include/achat.h \
    include/achat.h \
    include/config.h

FORMS    += ui/mainwindow.ui \
    ui/dialog.ui \
    ui/registr.ui \
    ui/form.ui \
    ui/kabinet.ui \
    ui/loading.ui
RESOURCES     = app.qrc

DISTFILES +=
