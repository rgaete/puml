
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nodes.h"
#include "nodefactory.h"
#include "assert.h"
#include <map>

class Document : public QObject
{
    Q_OBJECT

public:
    Document();
    ~Document();
    void addNode(BaseNode *newNode) { nodes.push_back(newNode); }
    void setNewObjectID(int prototypeID);
    int getNewObjectID() { return newObjectID; }
    int getCanvasIndex() { return canvasIndex; }
    void setCanvasIndex(int index) { canvasIndex = index; }
private:
    vector<BaseNode*> nodes;
    int indexOfSelectedObject;
    int newObjectID;
    QPoint positionDelta;
    int canvasIndex;
    QPoint tempPoint1;
signals:
    void modelChanged();

public slots:
    void drawList(QPainter &painter);
    void setSelectedObject(const QPoint &point);
    void moveSelectedObject(const QPoint &point);
    void createObject(const QPoint &position);
    void createConnectionPoint1(const QPoint &point);
    void createConnectionPoint2(const QPoint &point);
    void showPropertiesDialog();
};
#endif // DOCUMENT_H
