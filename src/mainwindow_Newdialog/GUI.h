#ifndef GUI_H
#define GUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QActionGroup>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <QPrinter>
#include <QPrintDialog>
#include "mainwindow.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionPrint;
    QAction *actionImport_Export;
    QAction *actionExit;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionSelect;
    QAction *actionSelect_All;
    QAction *actionInverse_Select;
    QActionGroup *Shapes_Connectors;
    QAction *actionCircle;
    QAction *actionDiamond;
    QAction *actionRectangle;
    QAction *actionStickMan;
    QAction *actionArrow;
    QAction *actionLine;
    QAction *actionDotted_Line;
    QAction *actionTile_Horizontally;
    QAction *actionTile_Vertically;
    QAction *actionCascade;
    QAction *actionDocument;
    QAction *actionAbout;
    QWidget *centralWidget;
    QScrollBar *verticalScrollBar;
    QScrollBar *horizontalScrollBar_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuTools;
    QMenu *menuShapes;
    QMenu *menuConnectors;
    QMenu *menuWindow;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow, int diagramType)
    {
        if (MainWindow->objectName().isEmpty())
          MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(673, 454);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionImport_Export = new QAction(MainWindow);
        actionImport_Export->setObjectName(QString::fromUtf8("actionImport_Export"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionSelect = new QAction(MainWindow);
        actionSelect->setObjectName(QString::fromUtf8("actionSelect"));
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName(QString::fromUtf8("actionSelect_All"));
        actionInverse_Select = new QAction(MainWindow);
        actionInverse_Select->setObjectName(QString::fromUtf8("actionInverse_Select"));

        Shapes_Connectors = new QActionGroup(MainWindow);
        Shapes_Connectors -> setExclusive(true);

        actionCircle = new QAction(MainWindow);
        actionCircle->setObjectName(QString::fromUtf8("actionCircle"));
        actionCircle->setCheckable(true);
        Shapes_Connectors->addAction(actionCircle);

        actionDiamond = new QAction(MainWindow);
        actionDiamond->setObjectName(QString::fromUtf8("actionDiamond"));
        actionDiamond->setCheckable(true);
        Shapes_Connectors->addAction(actionDiamond);

        actionRectangle = new QAction(MainWindow);
        actionRectangle->setObjectName(QString::fromUtf8("actionRectangle"));
        actionRectangle->setCheckable(true);
        Shapes_Connectors->addAction(actionRectangle);

        actionStickMan = new QAction(MainWindow);
        actionStickMan->setObjectName(QString::fromUtf8("actionStickMan"));
        actionStickMan->setCheckable(true);
        Shapes_Connectors->addAction(actionStickMan);

        actionArrow = new QAction(MainWindow);
        actionArrow->setObjectName(QString::fromUtf8("actionArrow"));
        actionArrow->setCheckable(true);
        Shapes_Connectors->addAction(actionArrow);

        actionLine = new QAction(MainWindow);
        actionLine->setObjectName(QString::fromUtf8("actionLine"));
        actionLine->setCheckable(true);
        Shapes_Connectors->addAction(actionLine);

        actionDotted_Line = new QAction(MainWindow);
        actionDotted_Line->setObjectName(QString::fromUtf8("actionDotted_Line"));
        actionDotted_Line->setCheckable(true);
        Shapes_Connectors->addAction(actionDotted_Line);


        actionTile_Horizontally = new QAction(MainWindow);
        actionTile_Horizontally->setObjectName(QString::fromUtf8("actionTile_Horizontally"));
        actionTile_Horizontally->setCheckable(true);
        actionTile_Vertically = new QAction(MainWindow);
        actionTile_Vertically->setObjectName(QString::fromUtf8("actionTile_Vertically"));
        actionTile_Vertically->setCheckable(true);
        actionCascade = new QAction(MainWindow);
        actionCascade->setObjectName(QString::fromUtf8("actionCascade"));
        actionCascade->setCheckable(true);
        actionDocument = new QAction(MainWindow);
        actionDocument->setObjectName(QString::fromUtf8("actionDocument"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalScrollBar = new QScrollBar(centralWidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(650, 0, 20, 401));
        verticalScrollBar->setOrientation(Qt::Vertical);
        horizontalScrollBar_2 = new QScrollBar(centralWidget);
        horizontalScrollBar_2->setObjectName(QString::fromUtf8("horizontalScrollBar_2"));
        horizontalScrollBar_2->setGeometry(QRect(0, 380, 651, 20));
        horizontalScrollBar_2->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 673, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuShapes = new QMenu(menuTools);
        menuShapes->setObjectName(QString::fromUtf8("menuShapes"));
        menuConnectors = new QMenu(menuTools);
        menuConnectors->setObjectName(QString::fromUtf8("menuConnectors"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QString::fromUtf8("menuWindow"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);


        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addSeparator();
        menuFile->addAction(actionImport_Export);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionPaste);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelect);
        menuEdit->addAction(actionSelect_All);
        menuEdit->addAction(actionInverse_Select);
        menuTools->addAction(menuShapes->menuAction());
        menuTools->addAction(menuConnectors->menuAction());



        menuShapes->addAction(actionStickMan);

        menuShapes->addAction(actionCircle);
        menuShapes->addAction(actionDiamond);
        menuShapes->addAction(actionRectangle);

        menuConnectors->addAction(actionArrow);
        menuConnectors->addAction(actionLine);
        menuConnectors->addAction(actionDotted_Line);
        menuWindow->addAction(actionTile_Horizontally);
        menuWindow->addAction(actionTile_Vertically);
        menuWindow->addAction(actionCascade);
        menuHelp->addAction(actionDocument);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);
        if(diagramType==None)
        {
          menuEdit->setDisabled(true);
          menuTools->setDisabled(true);
          menuShapes->setDisabled(true);
          menuWindow->setDisabled(true);
        }
        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "Create New pUML File", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Open a exsiting pUML file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave->setToolTip(QApplication::translate("MainWindow", "Save current work into file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As..", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_As->setToolTip(QApplication::translate("MainWindow", "Save current work into another file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionPrint->setText(QApplication::translate("MainWindow", "Print", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPrint->setToolTip(QApplication::translate("MainWindow", "Print the current work", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionImport_Export->setText(QApplication::translate("MainWindow", "Import/Export", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionImport_Export->setToolTip(QApplication::translate("MainWindow", "Import/Export from/to other UML type file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionCopy->setText(QApplication::translate("MainWindow", "Copy", 0, QApplication::UnicodeUTF8));
        actionCut->setText(QApplication::translate("MainWindow", "Cut", 0, QApplication::UnicodeUTF8));
        actionPaste->setText(QApplication::translate("MainWindow", "Paste", 0, QApplication::UnicodeUTF8));
        actionSelect->setText(QApplication::translate("MainWindow", "Select", 0, QApplication::UnicodeUTF8));
        actionSelect_All->setText(QApplication::translate("MainWindow", "Select All", 0, QApplication::UnicodeUTF8));
        actionInverse_Select->setText(QApplication::translate("MainWindow", "Inverse Select", 0, QApplication::UnicodeUTF8));
        actionCircle->setText(QApplication::translate("MainWindow", "Circle", 0, QApplication::UnicodeUTF8));
        actionDiamond->setText(QApplication::translate("MainWindow", "Diamond", 0, QApplication::UnicodeUTF8));
        actionRectangle->setText(QApplication::translate("MainWindow", "Rectangle", 0, QApplication::UnicodeUTF8));
        actionStickMan->setText(QApplication::translate("MainWindow", "StickMan", 0, QApplication::UnicodeUTF8));
        actionArrow->setText(QApplication::translate("MainWindow", "Arrow Line", 0, QApplication::UnicodeUTF8));
        actionLine->setText(QApplication::translate("MainWindow", "Straight Line", 0, QApplication::UnicodeUTF8));
        actionDotted_Line->setText(QApplication::translate("MainWindow", "Dotted Line", 0, QApplication::UnicodeUTF8));
        actionTile_Horizontally->setText(QApplication::translate("MainWindow", "Tile Horizontally", 0, QApplication::UnicodeUTF8));
        actionTile_Vertically->setText(QApplication::translate("MainWindow", "Tile Vertically", 0, QApplication::UnicodeUTF8));
        actionCascade->setText(QApplication::translate("MainWindow", "Cascade", 0, QApplication::UnicodeUTF8));
        actionDocument->setText(QApplication::translate("MainWindow", "Help Document", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
        menuShapes->setTitle(QApplication::translate("MainWindow", "Shapes", 0, QApplication::UnicodeUTF8));
        menuConnectors->setTitle(QApplication::translate("MainWindow", "Connectors", 0, QApplication::UnicodeUTF8));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

private:
    enum diagramType { None=0, UseCase=1, Class=2, Activity=3, Interaction=4, State=5};
};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // GUI_H
