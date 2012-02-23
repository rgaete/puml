/*! @file UMlnodes_class.h
    @brief Defines concrete Objectnodes and Connectionnodes that specific to
           class diagrams.

  */
#ifndef UMLNODES_CLASS_H
#define UMLNODES_CLASS_H

#include "nodes.h"
#include <QInputDialog>

/** @brief The properties dialog for class connections
**/
class ClassConnectionDialog : public QInputDialog {

};

/*! @brief This concrete class defines ...
*/
class ClassConnection : public ConnectionNode
{
public:
    BaseNode* clone() { return new ClassConnection; }
    bool hitTest(const QPoint &point) {point.x(); return false;}
    QDialog* getDialog() { return new ClassConnectionDialog; }
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Class Line"; }
    void draw(QPainter& painter);
    DiagramType getDiagramType() { return Class; }

};

#endif // UMLNODES_CLASS_H
