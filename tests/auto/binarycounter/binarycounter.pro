QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

INCLUDEPATH += ../../../src

SOURCES +=  testbinarycounter.cpp \
            ../../../src/binarystring.cpp \
            ../../../src/statisticalmap3d.cpp \
            ../../../src/findclusters3d.cpp
