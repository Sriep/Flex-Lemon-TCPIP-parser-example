TEMPLATE = app
CONFIG += console c++11
CONFIG += app_bundle
CONFIG += qt
QT += core gui
QT += network widgets

SOURCES += main.cpp \
    server.cpp \
    ../UtClient/commandlist.cpp

HEADERS += \
    server.h \
    ../UtClient/commandlist.h
