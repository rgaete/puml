// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_DOCUMENT_H_
#define SRC_DOCUMENT_H_

#include <assert.h>
#include <vector>
#include "./nodes.h"
#include "./nodefactory.h"

class Document : public QObject {
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
    int getIndexAt(const QPoint &point);

    // The main vector of nodes
    vector<BaseNode*> nodes;
    // The index of the selected object, -1 if nothing's selected
    int indexOfSelectedObject;
    // The prototypeID of the next object to create
    int newObjectID;
    // The difference between where a user clicked on the
    // object and the actual position of that object
    QPoint positionDelta;
    // A member variable that could be used to store the index
    // the currently connected canvas (Not used yet - 2/13/12)
    int canvasIndex;
    // This is the first object when creating a connection node
    int firstConnectionIndex;

  signals:
    void modelChanged();

  public slots:
    void drawList(QPainter &painter);  // NOLINT
    void setSelectedObject(const QPoint &point);
    void moveSelectedObject(const QPoint &point);
    void createObject(const QPoint &position);
    void createConnectionPoint1(const QPoint &point);
    void createConnectionPoint2(const QPoint &point);
    void showPropertiesDialog();
    void removeObject();
};

#endif  // SRC_DOCUMENT_H_
