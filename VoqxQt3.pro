#-------------------------------------------------
#
# Project created by QtCreator 2013-09-25T09:11:42
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VoqxQt3
TEMPLATE = app

CONFIG+=c++11

#INCLUDEPATH = /usr/include/flycapture
#INCLUDEPATH += /usr/include/triclops

#LIBS = -L/usr/src/flycapture/lib -lflycapture${D}
#LIBS += -ltriclops -lpnmutils -lflycapture -lflycapture2bridge -lpthread -ldl -lm

SOURCES += main.cpp\
    Arquivo.cpp \
    Controlador.cpp \
    Modelo.cpp \
    Voxel.cpp \
    mainwindow.cpp \
    TelaModelo.cpp \
    Video.cpp \
    TelaVideo.cpp \
    CanvasModelo.cpp \
    CanvasVideo.cpp \
    Canvas.cpp \
    rply.c \
    CanvasCamera.cpp \
    Camera.cpp \
    TelaCamera.cpp

HEADERS  += \
    Arquivo.h \
    Controlador.h \
    Modelo.h \
    Voxel.h \
    mainwindow.h \
    TelaModelo.h \
    Video.h \
    TelaVideo.h \
    CanvasModelo.h \
    CanvasVideo.h \
    Canvas.h \
    rply.h \
    rplyfile.h \
    CanvasCamera.h \
    Camera.h \
    TelaCamera.h

FORMS    += \
    mainwindow.ui \
    TelaVideo.ui \
    TelaModelo.ui \
    TelaCamera.ui

RESOURCES += \
    icons.qrc
