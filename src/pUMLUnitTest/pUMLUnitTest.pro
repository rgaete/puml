#-------------------------------------------------
#
#
#
#------------------------------------------------

QT       += core gui
QT       += xml
QT       += testlib

TARGET = pUMLUnitTest
TEMPLATE = app

CONFIG -= app_bundle

SOURCES += main.cpp \
    ../mainwindow.cpp \
    ../canvas.cpp \
    ../nodes.cpp \
    ../nodefactory.cpp \
    ../document.cpp \
    ../dialog.cpp \
    ../UMLnodes_class.cpp \
    ../UMLnodes_usecase.cpp \
    ../mathfunctions.cpp \
    ../UMLnodes_state.cpp \
    ../UMLnodes_collab.cpp \
    nodefactorytest.cpp \
    mainwindow_test.cpp \
    document_test.cpp

HEADERS  += nodefactorytest.h \
    ../mainwindow.h \
    ../canvas.h \
    ../nodes.h \
    ../nodefactory.h \
    ../UMLnodes.h \
    ../document.h \
    ../nodeaction.h \
    ../dialog.h \
    ../UMLnodes_usecase.h \
    ../UMLnodes_class.h \
    ../mathfunctions.h \
    ../UMLnodes_state.h \
    ../UMLnodes_collab.h \
    mainwindow_test.h \
    document_test.h

OTHER_FILES +=

RESOURCES += \
    ../icons.qrc
