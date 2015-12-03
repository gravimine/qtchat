#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T16:56:23
#
#-------------------------------------------------
QMAKE_CXXFLAGS_DEBUG += -pg
QMAKE_LFLAGS_DEBUG += -pg
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UChat
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    achat.cpp \
    acore.cpp \
    anetwork.cpp \
    ui.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    registr.h \
    form.h \
    kabinet.h \
    acore.h \
    anetwork.h \
    aclientserver.h \
    auimanager.h \
    loading.h \
    amath.h \
    achat.h

FORMS    += mainwindow.ui \
    dialog.ui \
    registr.ui \
    form.ui \
    kabinet.ui \
    loading.ui
RESOURCES     = app.qrc
