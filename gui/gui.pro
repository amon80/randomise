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

INCLUDEPATH += ../src

SOURCES += main.cpp\
        mainwindow.cpp \
    evstab.cpp \
    contrasttab.cpp \
    ../src/myvmp.cpp \
    ../src/binaryio.cpp \
    ../src/statisticalmap4d.cpp \
    ../src/multyrowarray.cpp \
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
