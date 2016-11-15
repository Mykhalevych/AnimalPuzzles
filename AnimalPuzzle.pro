#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T13:01:27
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AnimalPuzzles
TEMPLATE = app


SOURCES += main.cpp\
        mwidget.cpp \
    glogo.cpp \
    gmenumain.cpp \
    ppbasescene.cpp \
    pplocale.cpp \
    ppsettings.cpp \
    ppsound.cpp \
    ppobjclasses.cpp \
    ggamescreen.cpp \
    gitembase.cpp \
    glevel01.cpp \
    glevel02.cpp

HEADERS  += mwidget.h \
    glogo.h \
    gmenumain.h \
    gstructures.h \
    ppbasescene.h \
    pplocale.h \
    ppsettings.h \
    ppsound.h \
    ppobjclasses.h \
    ggamescreen.h \
    gitembase.h \
    glevel01.h \
    glevel02.h

CONFIG += mobility
MOBILITY = 

RESOURCES += \
    resource.qrc

