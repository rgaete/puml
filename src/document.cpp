// Copyright (C) 2011-2012 pUML Group

#include <QMessageBox>
#include <list>
#include "./document.h"

/*! Constructor: simply initializes indexOfSelectedObject.
*/
Document::Document() {
  indexOfSelectedObject = -1;
}

/*! Destructor: frees up the memory used up by the vector of nodes.
  @bug There is an intermitten bug where an exception will be thrown
     by .at()!
*/
Document::~Document() {
  for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
    assert(nodes.at(i) != 0);
    // QMessageBox::information(0, "node text", nodes.at(i)->getText(),
    //                          QMessageBox::Ok, QMessageBox::Ok);
    delete nodes.at(i);
  }
}

/*! Slot. Updates indexOfSelectedObject based on point. Uses the
  hitTest function of BaseNode. Sets to -1 if no hitTests return
  true.
*/
void Document::setSelectedObject(const QPoint &point) {
  assert(indexOfSelectedObject >= -1);
  assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  // reset the selected property of previously
  // selected node
  if (indexOfSelectedObject != -1) {
    nodes.at(indexOfSelectedObject)->setSelected(false);
  }

  // start at the end of the vector and find the
  // first object with a positive hittest.
  indexOfSelectedObject = getIndexAt(point);
  if (indexOfSelectedObject != -1) {
    nodes.at(indexOfSelectedObject)->setSelected(true);
  }

  // Save the difference between where the mouse click was (point) and
  // where the actual middle of the object is. This will be used to
  // acurately move and drag the object.
  if (indexOfSelectedObject != -1) {
    positionDelta = nodes.at(indexOfSelectedObject)->getPosition() - point;
  }

  // at this point a redraw is needed to show the new
  // highlighted object.
  emit modelChanged();
}

/*! Slot. Updates the prototypeID for the next object to be created.
  The signal with the ID should come from the MainWindow with the
  ID being stored in a NodeAction created by MainWindow.registerPrototype()
*/
void Document::setNewObjectID(int prototypeID) {
  newObjectID = prototypeID;
}

int Document::getIndexAt(const QPoint &point) {
  int index = -1;
  for (int i = nodes.size() - 1; i >= 0; i--) {
    if (nodes.at(i)->hitTest(point) == true) {
      index = i;
      break;
    }
  }

  return index;
}

/*! Slot. This will move whatever object is selected to the new point, while
  adding in the delta that was saved by a previous call to setSelectedObject.
*/
void Document::moveSelectedObject(const QPoint &point) {
  assert(indexOfSelectedObject >= -1);
  assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  if (indexOfSelectedObject != -1) {
    nodes.at(indexOfSelectedObject)->setPosition(point + positionDelta);
  }

  emit modelChanged();
}

/*! Slot. This will create a new object at the specified position. The
  prototypeID of the new object will have been set by a previous signal
  to setNewObjectID. Uses NodeFactory.
*/
void Document::createObject(const QPoint &position) {
  assert(indexOfSelectedObject >= -1);
  assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  // create a new node using the factory
  BaseNode* newNode;
  newNode = NodeFactory::getInstance()->produce(newObjectID);
  newNode->setPosition(position);

  // add newnode to a vector of nodes.
  addNode(newNode);

  // reset the selected property of previously selected node
  if (indexOfSelectedObject != -1) {
    nodes.at(indexOfSelectedObject)->setSelected(false);
  }

  // set the selected index to be the created object
  indexOfSelectedObject = nodes.size()-1;
  nodes.at(indexOfSelectedObject)->setSelected(true);

  emit modelChanged();
}

/*! Slot. Sets the object index in a new connection node.
  Sets firstConnectionIndex to either some valid index or
  -1 if the first connection point is invalid.
*/
void Document::createConnectionPoint1(const QPoint &point) {
  // Find the object under the point. -1 signifies either
  // no object found or connector found
  firstConnectionIndex = getIndexAt(point);
  if ((firstConnectionIndex != -1) &&
      (nodes.at(firstConnectionIndex)->isConnector() == true)) {
    firstConnectionIndex = -1;
  }
}

/*! Slot. Sets the second point in a new connection node.
  This function actually creates the node using the NodeFactory.
  It doesn't create the node if the first or second point is invalid.
*/
void Document::createConnectionPoint2(const QPoint &point) {
  // Create the object only if a valid first object was found
  if (firstConnectionIndex != -1) {
    int index = getIndexAt(point);
    // And the second index was found
    if ((index != -1) && (nodes.at(index)->isConnector() == false)) {
      // produce the object
      BaseNode *newNode;
      newNode = NodeFactory::getInstance()->produce(newObjectID);

      // now connect the connection to both objects, and connect the
      // objects to the connections
      newNode->addConnectedNode(nodes.at(firstConnectionIndex));
      newNode->addConnectedNode(nodes.at(index));
      nodes.at(firstConnectionIndex)->addConnectedNode(newNode);
      nodes.at(index)->addConnectedNode(newNode);

      addNode(newNode);
      emit modelChanged();
    }
  }
}

/*! Slot. This will ask for a new dialog with BaseNode.getDialog
  and show it modally. It is the dialog's responsibility to make
  whatever changes are necessary to the node.
*/
void Document::showPropertiesDialog() {
  assert(indexOfSelectedObject >= -1);
  assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

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
void Document::drawList(QPainter &painter) {  // NOLINT
  for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
    nodes[i]->draw(painter);
  }
}

void Document::removeObject() {
  assert(indexOfSelectedObject >= -1);
  assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  if (indexOfSelectedObject != -1) {
    BaseNode* obj = nodes.at(indexOfSelectedObject);
    if (obj->isConnector() == false) {
      // erase all the connected connectionnodes
      // get the list of connected nodes, which are all connections
      std::list<BaseNode*> objs;
      objs = obj->getConnectedNodes();

      // iterator through that list and delete the connection nodes
      // as well as remove the pointers to this node from all objects
      // that are connected to the connection node
      std::list<BaseNode*>::iterator it;
      for (it = objs.begin(); it != objs.end(); ++it) {
        // for each of the objects that are connected to this connection,
        std::list<BaseNode*> secondaryObject;
        std::list<BaseNode*>::iterator it2;
        for (it2 = secondaryObject.begin(); it2 != secondaryObject.end(); ++it) {  // NOLINT
          // remove the connection back to the connectionode we are deleting
          (*it2)->removeConnectedNode(*it);
        }

        // delete this connection node
        for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
          if (nodes.at(i) == (*it)) {
            nodes.erase(nodes.begin()+i);
          }
        }
      }
      // now actually erase the object
      nodes.erase(nodes.begin()+indexOfSelectedObject);
    } else {
      // get the list of connected objects (should only be two objects)
      std::list<BaseNode*> secondaryObjects;
      secondaryObjects = obj->getConnectedNodes();

      // iterate through the list and disconnect the connectionnode we
      // are deleting from the objects.
      std::list<BaseNode*>::iterator it;
      for (it = secondaryObjects.begin(); it != secondaryObjects.end(); ++it) {
        (*it)->removeConnectedNode(obj);
      }

      // now delete the actual node
      nodes.erase(nodes.begin()+indexOfSelectedObject);
    }
  }

  indexOfSelectedObject = -1;
  emit modelChanged();
}
