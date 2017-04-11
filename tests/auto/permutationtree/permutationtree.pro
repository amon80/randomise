QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../src

SOURCES +=  testpermutationtree.cpp \
            ../../../src/permutationtreeblock.cpp \
            ../../../src/permutationtree.cpp \
            ../../../src/threecolsarray.cpp \
            ../../../src/binarystring.cpp \
            ../../../src/mymath.cpp \
            ../../../src/matrices.cpp

