#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T17:05:19
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = L-System_Designer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    LSystem.cpp \
    Variable.cpp \
    VariableSequence.cpp

HEADERS  += MainWindow.h \
    LSystem.h \
    Variable.h \
    VariableSequence.h

FORMS    += MainWindow.ui
