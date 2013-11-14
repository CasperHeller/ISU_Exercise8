TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++0x -pthread

DEFINES += OS_LINUX

SOURCES += main.cpp \
    carclass.cpp \
    entryclass.cpp \
    exitclass.cpp

HEADERS += \
    carclass.h \
    entryclass.h \
    exitclass.h \
    types.h

unix|win32: LIBS += -L$$PWD/../Exercise_1+2/lib/host/release/ -lOSApi

INCLUDEPATH += $$PWD/../Exercise_1+2/inc
DEPENDPATH += $$PWD/../Exercise_1+2/inc

win32: PRE_TARGETDEPS += $$PWD/../Exercise_1+2/lib/host/release/OSApi.lib
else:unix: PRE_TARGETDEPS += $$PWD/../Exercise_1+2/lib/host/release/libOSApi.a
