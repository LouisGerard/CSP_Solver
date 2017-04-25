TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    common.c

HEADERS += \
    common.h

QMAKE_CFLAGS += -std=c99
