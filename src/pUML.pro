#-------------------------------------------------
#
# Project created by QtCreator 2011-12-04T23:27:29
#
#------------------------------------------------
#
# THis is a change

QT       += core gui
QT       += xml

TARGET = pUML
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    nodes.cpp \
    nodefactory.cpp \
    document.cpp \
    dialog.cpp \
    UMLnodes_class.cpp \
    UMLnodes_usecase.cpp \
    mathfunctions.cpp \
    UMLnodes_state.cpp \
    UMLnodes_collab.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    nodes.h \
    nodefactory.h \
    UMLnodes.h \
    document.h \
    nodeaction.h \
    dialog.h \
    UMLnodes_usecase.h \
    UMLnodes_class.h \
    mathfunctions.h \
    UMLnodes_state.h \
    UMLnodes_collab.h

OTHER_FILES +=

RESOURCES += \
    icons.qrc
