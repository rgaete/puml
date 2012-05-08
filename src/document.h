// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_DOCUMENT_H_
#define SRC_DOCUMENT_H_

#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QMessageBox>

#include <assert.h>
#include <list>
#include <string>
#include <vector>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>


#include "./nodefactory.h"
#include "./nodes.h"
#include "./UMLnodes.h"

// void experiment(QString openName);

class Document : public QWidget {
  Q_OBJECT

  public:
    Document();
    // Document(QString fpath);
    ~Document();
    void addNodeToList(BaseNode *newNode) { nodes.push_back(newNode); }
    void setNewObjectID(int prototypeID);
    int getNewObjectID() { return newObjectID; }
    void setCanvasIndex(int index) { canvasIndex = index; }
    int getCanvasIndex() { return canvasIndex; }
    BaseNode::DiagramType getDiagramType() { return diagramType; }
    void saveDocument();
    void openDocument(QString openName);
    bool hasFilename() { if (fileName == "") { return false; } else { return true; } }
    void setFilename(QString newfilename) {
        fileName = newfilename;
        QMessageBox::information(this, "pUML", "Setting filename: "  + fileName);
    }
    bool getModified() { return modifiedFlag; }

    // @TODO Once the saveAs functionality is moved into this class from
    // mainwindow, move nodes back to private.
    // The main vector of nodes
  private:
    std::vector<BaseNode*> nodes;

  private:
    int getIndexAt(const QPoint &point);
    void removeFromOrdering(int index);
    void setModified(bool modified);
    BaseNode* findNodeById(QUuid id);

    // The index of the selected object, -1 if nothing's selected
    int indexOfSelectedObject;
    // The prototypeID of the next object to create
    int newObjectID;
    // The difference between where a user clicked on the
    // object and the actual position of that object
    QPoint positionDelta;
    // A member variable that could be used to store the index
    // the currently connected canvas
    int canvasIndex;
    // This is the first object when creating a connection node
    int firstConnectionIndex;
    // The index of the second connection point hint, i.e., objects
    // that the mouse moves over when drawing a connection
    int secondConnectionIndex;
    // the list of indexes to objects to draw.
    QList<int> ordering;
    // the type of diagram that this canvas has
    BaseNode::DiagramType diagramType;
    // The filename for this document.
    QString fileName;
    // Whether the document has been modifed
    bool modifiedFlag;

  signals:
    void modelChanged();
    void modifiedChanged(bool modified);

  public slots:
    void drawList(QPainter &painter);  // NOLINT
    void setSelectedObject(const QPoint &point);
    void moveSelectedObject(const QPoint &point);
    void createObject(const QPoint &position);
    void createConnectionPoint1(const QPoint &point);
    void createConnectionPoint2(const QPoint &point);
    void showPropertiesDialog();
    void removeObject();
    void sendSelectedToFront();
    void sendSelectedForward();
    void sendSelectedToBack();
    void sendSelectedBackwards();
    void setDiagramType(BaseNode::DiagramType type) { diagramType = type; }
    void changeSecondConnectionPointHint(const QPoint &point);
};

#endif  // SRC_DOCUMENT_H_
