#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T17:05:19
#
#-------------------------------------------------

QT       += core gui opengl script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = L-System_Designer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    LSystem.cpp \
    Variable.cpp \
    VariableSequence.cpp \
    Production.cpp \
    VariableSequenceModel.cpp \
    DialogCreateVariable.cpp \
    ProductionTableModel.cpp \
    SpinBoxDelegate.cpp \
    VariableSequenceListModel.cpp \
    DialogCreateAxiom.cpp \
    Simulator.cpp \
    VariableSequenceRenderer.cpp

HEADERS  += MainWindow.h \
    LSystem.h \
    Variable.h \
    VariableSequence.h \
    Production.h \
    VariableSequenceModel.h \
    DialogCreateVariable.h \
    ProductionTableModel.h \
    SpinBoxDelegate.h \
    VariableSequenceListModel.h \
    DialogCreateAxiom.h \
    Simulator.h \
    VariableSequenceRenderer.h

FORMS    += MainWindow.ui \
    DialogCreateVariable.ui \
    DialogCreateAxiom.ui
