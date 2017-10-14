#-------------------------------------------------
#
# Project created by QtCreator 2017-10-13T22:55:06
#
#-------------------------------------------------

QT       -= gui

CONFIG += console c++11
CONFIG += c++11
TARGET = MEPCore
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++11

DEFINES += MEPCORE_LIBRARY

SOURCES += \
    object.cpp \
    main.cpp

HEADERS +=\
    types.h \
    mepcore_global.h \
    object.h \
    gene.h \
    terminalgene.h \
    functiongene.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
