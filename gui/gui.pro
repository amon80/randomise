QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RandomiseGui
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++11

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp


INCLUDEPATH += ../src

SOURCES += main.cpp\
        mainwindow.cpp \
    evstab.cpp \
    contrasttab.cpp \
    ../src/myvmp.cpp \
    ../src/myvmpheader.cpp \
    ../src/binaryio.cpp \
    ../src/statisticalmap4d.cpp \
    ../src/multyrowarray.cpp \
    ../src/randomise.cpp \
    ../src/statisticalmap3d.cpp \
    ../src/permutationtree.cpp \
    ../src/mymath.cpp \
    ../src/mystat.cpp \
    ../src/tfce.cpp \
    ../src/permutationtreeblock.cpp \
    ../src/threecolsarray.cpp \
    ../src/matrices.cpp \
    ../src/connectivity3d.cpp \
    ../src/connectivity3d6.cpp \
    ../src/connectivity3d18.cpp \
    ../src/connectivity3d26.cpp \
    ../src/binarystring.cpp \
    ../src/point3d.cpp \
    evstabuppermiddlepart.cpp \
    evstabmiddlepart.cpp \
    evstabbottompart.cpp \
    evstabbottomcontent.cpp \
    contrasttabtoppart.cpp \
    contrasttabuppermiddlepart.cpp \
    evscolumnslabels.cpp \
    ftestcolumnslabels.cpp \
    contrasttabmiddlepart.cpp \
    contrasttabmiddlepartcontent.cpp \
    evsspinboxes.cpp \
    ftestscheckboxes.cpp \
    filetab.cpp \
    optionstab.cpp \
    filetabtoppart.cpp \
    optionstabnumberpermutationpart.cpp \
    optionstabinferencelevelpart.cpp \
    optionstabusetfcepart.cpp

HEADERS  += mainwindow.h \
    evstab.h \
    contrasttab.h \
    evstabuppermiddlepart.h \
    evstabmiddlepart.h \
    evstabbottompart.h \
    evstabbottomcontent.h \
    contrasttabtoppart.h \
    contrasttabuppermiddlepart.h \
    evscolumnslabels.h \
    ftestcolumnslabels.h \
    contrasttabmiddlepart.h \
    contrasttabmiddlepartcontent.h \
    evsspinboxes.h \
    ftestscheckboxes.h \
    filetab.h \
    optionstab.h \
    filetabtoppart.h \
    optionstabnumberpermutationpart.h \
    optionstabinferencelevelpart.h \
    optionstabusetfcepart.h
