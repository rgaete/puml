#include "document.h"
#include <QMessageBox>

Document::Document()
{
    indexOfSelectedObject = -1;
}

Document::~Document()
{
    for (int i=0; i<(int)nodes.size(); i++) {
        delete nodes.at(i);
    }
}

void Document::setSelectedObject(const QPoint &point)
{
    assert(indexOfSelectedObject >= -1);
    assert(indexOfSelectedObject < (int)nodes.size());

    //reset the selected property of previously
    //selected node
    if (indexOfSelectedObject != -1) {
        nodes.at(indexOfSelectedObject)->setSelected(false);
    }

    //start at the end of the vector and find the
    //first object with a positive hittest.
    indexOfSelectedObject = -1;
    for (int i=nodes.size()-1; i>=0; i--) {
        if (nodes.at(i)->hitTest(point) == true) {
            indexOfSelectedObject = i;
            nodes.at(i)->setSelected(true);
            break;
        }
    }

    //Save the difference between where the mouse click was (point) and
    //where the actual middle of the object is. This will be used to
    //acurately move and drag the object.
    if (indexOfSelectedObject != -1) {
        positionDelta = nodes.at(indexOfSelectedObject)->getPosition() - point;
    }

    //at this point a redraw is needed to show the new
    //highlighted object. It is assumed that the calling
    //widget will redraw after calling the
    emit modelChanged();
}

void Document::setNewObjectID(int prototypeID)
{
    newObjectID = prototypeID;
}


void Document::moveSelectedObject(const QPoint &point)
{
    assert(indexOfSelectedObject >= -1);
    assert(indexOfSelectedObject < (int)nodes.size());

    if (indexOfSelectedObject != -1) {
        nodes.at(indexOfSelectedObject)->setPosition(point + positionDelta);
    }

    emit modelChanged();
}

void Document::createObject(const QPoint &position)
{
    //create a new node using the factory
    //QMessageBox::information(0, "pUML", QString::number(nodes.size()), QMessageBox::Ok);
    BaseNode* newNode;
    //Note: this slot needs access to the factory (Singleton)
    newNode = NodeFactory::getInstance()->produce(newObjectID);
    newNode->setPosition(position);

    //show dialog box here?

    //add newnode to a vector of nodes.
   addNode(newNode);
   //QMessageBox::information(0, "pUML", QString::number(nodes.size()), QMessageBox::Ok);

   emit modelChanged();
}

void Document::drawList(QPainter &painter)
{
    for (int i=0; i<(int)nodes.size(); i++) {
        nodes[i]->draw(painter);
    }
}
