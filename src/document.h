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

private:
    vector<BaseNode*> nodes;
    int indexOfSelectedObject;
    int newObjectID;
    QPoint positionDelta;


signals:
    void modelChanged();

public slots:
    void drawList(QPainter &painter);
    void setSelectedObject(const QPoint &point);
    void moveSelectedObject(const QPoint &point);
    void createObject(const QPoint &position);
};

#endif // DOCUMENT_H
