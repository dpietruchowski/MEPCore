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
    core/object.cpp \
    main.cpp \
    utils/color.cpp \
    utils/random.cpp \
    genetic/selection.cpp \
    genetic/tournamentselection.cpp \
    genetic/rouletteselection.cpp \
    genetic/mutation.cpp \
    utils/log.cpp

HEADERS +=\
    mepcore_global.h \
    utils/types.h \
    core/object.h \
    core/gene.h \
    operation/operation.h \
    operation/function.h \
    operation/terminal.h \
    core/chromosome.h \
    utils/color.h \
    genetic/ptrset.h \
    utils/random.h \
    genetic/operationset.h \
    genetic/fitness.h \
    genetic/selection.h \
    genetic/tournamentselection.h \
    genetic/rouletteselection.h \
    genetic/mutation.h \
    genetic/crossover.h \
    core.h \
    genetic.h \
    operation.h \
    genetic/population.h \
    utils/log.h \
    utils/modules.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    core
