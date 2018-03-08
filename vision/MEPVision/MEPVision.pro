TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

DEPENDPATH += . "../../build-debug"
INCLUDEPATH += "../../src"
LIBS += -L"../../build-debug" -lMEPCore

QMAKE_CXXFLAGS += -std=c++11
LIBS += -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc

SOURCES += main.cpp \
    hammingfitness.cpp \
    image.cpp \
    functions.cpp \
    morphology.cpp

HEADERS += \
    hammingfitness.h \
    image.h \
    functions.h \
    morphology.h
