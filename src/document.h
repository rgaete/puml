
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "nodes.h"
#include "nodefactory.h"
#include "assert.h"

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
    //! The main vector of nodes
    vector<BaseNode*> nodes;
    //! The index of the selected object, -1 if nothing's selected
    int indexOfSelectedObject;
    //! The prototypeID of the next object to create
    int newObjectID;
    //! The difference between where a user clicked on the
    //! object and the actual position of that object
    QPoint positionDelta;
    //! A member variable that could be used to store the index
    //! the currently connected canvas (Not used yet - 2/13/12)
    int canvasIndex;
    //! This is first click when creating a connection node
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
    void removeObject();
};
#endif // DOCUMENT_H
