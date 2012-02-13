#include "document.h"
#include <QMessageBox>

/*! Constructor: simply initializes indexOfSelectedObject.
*/
Document::Document()
{
    indexOfSelectedObject = -1;
}

/*! Destructor: frees up the memory used up by the vector of nodes.
    @bug There is an intermitten bug where an exception will be thrown
         by .at()!
*/
Document::~Document()
{
    for (int i=0; i<(int)nodes.size(); i++) {
        assert(nodes.at(i) != 0);
        //QMessageBox::information(0, "node text", nodes.at(i)->getText(), QMessageBox::Ok, QMessageBox::Ok);
        delete nodes.at(i);
    }
}

/*! Slot. Updates indexOfSelectedObject based on point. Uses the
    hitTest function of BaseNode. Sets to -1 if no hitTests return
    true.
*/
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
    //highlighted object.
    emit modelChanged();
}

/*! Slot. Updates the prototypeID for the next object to be created.
    The signal with the ID should come from the MainWindow with the
    ID being stored in a NodeAction created by MainWindow.registerPrototype()
*/
void Document::setNewObjectID(int prototypeID)
{
    newObjectID = prototypeID;
}

/*! Slot. This will move whatever object is selected to the new point, while
    adding in the delta that was saved by a previous call to setSelectedObject.
*/
void Document::moveSelectedObject(const QPoint &point)
{
    assert(indexOfSelectedObject >= -1);
    assert(indexOfSelectedObject < (int)nodes.size());

    if (indexOfSelectedObject != -1) {
        nodes.at(indexOfSelectedObject)->setPosition(point + positionDelta);
    }

    emit modelChanged();
}

/*! Slot. This will create a new object at the specified position. The
    prototypeID of the new object will have been set by a previous signal
    to setNewObjectID. Uses NodeFactory.
*/
void Document::createObject(const QPoint &position)
{
    assert(indexOfSelectedObject >= -1);
    assert(indexOfSelectedObject < (int)nodes.size());

    //create a new node using the factory
    BaseNode* newNode;
    newNode = NodeFactory::getInstance()->produce(newObjectID);
    newNode->setPosition(position);

    //add newnode to a vector of nodes.
   addNode(newNode);

   //reset the selected property of previously selected node
   if (indexOfSelectedObject != -1) {
       nodes.at(indexOfSelectedObject)->setSelected(false);
   }

   //set the selected index to be the created object
   indexOfSelectedObject = nodes.size()-1;
   nodes.at(indexOfSelectedObject)->setSelected(true);

   emit modelChanged();
}

/*! Slot. Sets the first point in a new connection node.
    This function (should) determines if the point is over
    a valid node or not.
*/
void Document::createConnectionPoint1(const QPoint &point)
{
    tempPoint1 = point;
}

/*! Slot. Sets the second point in a new connection node.
    This function actually creates the node using the NodeFactory.
*/
void Document::createConnectionPoint2(const QPoint &point)
{
    BaseNode *newNode;
    newNode = NodeFactory::getInstance()->produce(newObjectID);
    newNode->setPoints(tempPoint1, point);
    addNode(newNode);
    emit modelChanged();
}

/*! Slot. This will ask for a new dialog with BaseNode.getDialog
    and show it modally. It is the dialog's responsibility to make
    whatever changes are necessary to the node.
*/
void Document::showPropertiesDialog()
{
    assert(indexOfSelectedObject >= -1);
    assert(indexOfSelectedObject < (int)nodes.size());

    if (indexOfSelectedObject != -1) {
        QDialog *properties;
        properties = nodes.at(indexOfSelectedObject)->getDialog();

        properties->exec();
        delete properties;
    }

    emit modelChanged();
}

/*! Slot. This will draw the nodes using painter. It assumes
    that painter is a valid painter, and uses BaseNode.draw().
*/
void Document::drawList(QPainter &painter)
{
    for (int i=0; i<(int)nodes.size(); i++) {
        nodes[i]->draw(painter);
    }
}
