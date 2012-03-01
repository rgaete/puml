// Copyright (C) 2011-2012 pUML Group

/*! @file UMlnodes_class.h
    @brief Defines concrete Objectnodes and Connectionnodes that specific to
           class diagrams.
  */
#ifndef SRC_UMLNODES_CLASS_H_
#define SRC_UMLNODES_CLASS_H_

#include <QInputDialog>
#include "./nodes.h"

/*! @brief The properties dialog for class connections
 */
class ClassConnectionDialog : public QInputDialog {
};

/*! @brief This concrete class defines ...
 */
class ClassConnection : public SquareConnectionNode {
  public:
    BaseNode* clone() { return new ClassConnection; }
    QDialog* getDialog() { return new ClassConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Class Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Class; }
};

#endif  // SRC_UMLNODES_CLASS_H_
