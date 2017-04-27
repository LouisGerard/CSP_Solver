TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    csp.c \
    ai.c

HEADERS += \
    csp.h \
    ai.h

QMAKE_CFLAGS += -std=c99
