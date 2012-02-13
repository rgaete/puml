#ifndef NODEACTION_H
#define NODEACTION_H

#include <QAction>
#include "canvas.h"

class NodeAction : public QAction {
    Q_OBJECT
public:
    NodeAction(Canvas::DrawingMode mode, int prototypeID, QObject *parent)
        : m_drawingMode(mode), m_prototypeID(prototypeID), QAction(parent)
    {
        connect(this, SIGNAL(triggered()), this, SLOT(onTriggered()));
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
};

#endif // NODEACTION_H
