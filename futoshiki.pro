#-------------------------------------------------
#
# Project created by QtCreator 2016-12-20T16:15:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = futoshiki
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grid.cpp \
    constraint_superiority.cpp \
    constraint_uniqueness.cpp \
    file.cpp \
    item.cpp \
    ai.cpp \
    assignment.cpp \
    basic_heuristic.cpp

HEADERS  += mainwindow.h \
    grid.h \
    constraint_superiority.h \
    constraint.h \
    constraint_uniqueness.h \
    file.h \
    item.h \
    ai.h \
    assignment.h \
    heuristic.h \
    basic_heuristic.h

FORMS    += mainwindow.ui
