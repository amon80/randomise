QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase c++11
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../src

SOURCES +=  testthreecolsarray.cpp \
            ../../../src/threecolsarray.cpp \
            ../../../src/mymath.cpp

