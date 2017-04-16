TEMPLATE = subdirs

SUBDIRS += src

SUBDIRS += gui

CONFIG(debug, debug|release) {
    SUBDIRS += tests
}
