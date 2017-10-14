#-------------------------------------------------
#
# Project created by QtCreator 2017-10-13T23:45:47
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = mepcoretest
CONFIG   += console
CONFIG   -= app_bundle

DEPENDPATH += . "../build-debug"
INCLUDEPATH += "../src"
LIBS += -L"../build-debug" -lMEPCore

TEMPLATE = app


SOURCES += \
    object_utest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
