#ifndef NODEACTION_H
#define NODEACTION_H

#include <QAction>
#include "canvas.h"


class NodeAction : public QAction {
    Q_OBJECT
public:
    NodeAction(Canvas::DrawingMode mode, int prototypeID, BaseNode::DiagramType diagramType, QObject *parent)
        : m_drawingMode(mode), m_prototypeID(prototypeID), m_diagramType(diagramType), QAction(parent)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
    }
    BaseNode::DiagramType getDiagramType()
    {
        return m_diagramType;
    }

signals:
    void triggered(Canvas::DrawingMode mode, int prototypeID);

public slots:
    void onTriggered()
    {
        emit triggered(m_drawingMode, m_prototypeID);
    }

private:
    Canvas::DrawingMode m_drawingMode;
    int m_prototypeID;
    BaseNode::DiagramType m_diagramType;
};

#endif // NODEACTION_H
