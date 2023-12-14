TEMPLATE = lib
CONFIG += plugin
QT += core widgets svg

INCLUDEPATH += $$PWD/plugininterface \
        $$PWD/onestepwindow \
        $$PWD
HEADERS = plugininterface/plugininterface.h \
        onestepwindow/onestepwindow.h \
        onestepwindow/passwordedit.h \
        onestep.h
SOURCES = plugininterface/plugininterface.cpp \
        onestepwindow/onestepwindow.cpp \
        onestep.cpp
FORMS = onestepwindow/onestepwindow.ui

TRANSLATIONS = onestep_zh_CN.ts \
        onestep_en_US.ts

RESOURCES = onestep.qrc

TARGET = $$qtLibraryTarget(onestep)

unix:{
    QMAKE_RPATHDIR=$ORIGIN
}
