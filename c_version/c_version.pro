TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    common.c \
    backtrack.c

HEADERS += \
    common.h \
    backtrack.h

QMAKE_CFLAGS += -std=c99
