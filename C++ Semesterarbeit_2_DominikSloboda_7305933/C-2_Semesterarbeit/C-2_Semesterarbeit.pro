QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spiel
TEMPLATE = app

SOURCES += main.cpp \
    healthpoints.cpp \
    spielfeld.cpp \
    Widget.cpp

HEADERS += \
    healthpoints.h \
    spielfeld.h \
    Widget.h
