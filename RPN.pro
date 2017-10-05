QT += core
QT -= gui

CONFIG += c++11

TARGET = RPN
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    rpn.cpp

HEADERS += \
    ListedQueue.h \
    Queue.h \
    rpn.h
