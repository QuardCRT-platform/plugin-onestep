TEMPLATE = lib
CONFIG += plugin
QT += core widgets

INCLUDEPATH += $$PWD/plugininterface \
        $$PWD
HEADERS = plugininterface/plugininterface.h \
        helloworld.h
SOURCES = plugininterface/plugininterface.cpp \
        helloworld.cpp

TARGET = $$qtLibraryTarget(helloworld)

unix:{
    QMAKE_RPATHDIR=$ORIGIN
}
