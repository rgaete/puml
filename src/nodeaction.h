// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_NODEACTION_H_
#define SRC_NODEACTION_H_

#include <QAction>
#include "./canvas.h"


class NodeAction : public QAction {
  Q_OBJECT

  public:
    NodeAction(Canvas::DrawingMode mode, int prototypeID,
               BaseNode::DiagramType diagramType, QObject *parent)
        :QAction(parent), m_drawingMode(mode),
         m_prototypeID(prototypeID), m_diagramType(diagramType) {
      connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
    }
    BaseNode::DiagramType getDiagramType() {
      return m_diagramType;
    }

  signals:
    void triggered(Canvas::DrawingMode mode, int prototypeID);

  public slots:
    void onTriggered() {
      emit triggered(m_drawingMode, m_prototypeID);
    }

  private:
    Canvas::DrawingMode m_drawingMode;
    int m_prototypeID;
    BaseNode::DiagramType m_diagramType;
};

#endif  // SRC_NODEACTION_H_
