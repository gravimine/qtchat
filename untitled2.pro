#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T16:56:23
#
#-------------------------------------------------
QT       += core gui network multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(ACore/ACore.pri)
TARGET = UChat
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    ui.cpp \
    achat.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    registr.h \
    form.h \
    kabinet.h \
    auimanager.h \
    loading.h \
    achat.h \
    achat.h

FORMS    += mainwindow.ui \
    dialog.ui \
    registr.ui \
    form.ui \
    kabinet.ui \
    loading.ui
RESOURCES     = app.qrc

DISTFILES +=
