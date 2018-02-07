QT += core
QT -= gui

TARGET = TP1_GN
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    vertex.cpp \
    face.cpp \
    mesh.cpp \
    halfedge.cpp

HEADERS += \
    vertex.h \
    face.h \
    mesh.h \
    halfedge.h

