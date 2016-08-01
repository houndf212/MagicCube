#-------------------------------------------------
#
# Project created by QtCreator 2016-07-07T10:36:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtgl
TEMPLATE = app


SOURCES += main.cpp\
        glwidget.cpp \
    shader.cpp \
    camera.cpp \
    cube.cpp \
    vertex.cpp \
    magiccube.cpp \
    ring.cpp \
    circle.cpp \
    draganalysis.cpp

HEADERS  += glwidget.h \
    shader.h \
    camera.h \
    cube.h \
    define.h \
    vertex.h \
    magiccube.h \
    ring.h \
    surface.h \
    block.h \
    circle.h \
    draganalysis.h

RESOURCES += \
    shaders.qrc
