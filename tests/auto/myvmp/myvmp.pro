QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../src

SOURCES +=  testmyvmp.cpp \
            ../../../src/myvmp.cpp \
            ../../../src/binaryio.cpp
