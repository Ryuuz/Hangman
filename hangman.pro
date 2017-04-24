#-------------------------------------------------
#
# Project created by QtCreator 2016-09-24T21:05:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hangman
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    button.cpp \
    consts.cpp \
    input.cpp

HEADERS  += \
    game.h \
    button.h \
    consts.h \
    input.h

FORMS    +=

RESOURCES += \
    resources.qrc
