// Copyright (C) 2011-2012 pUML Group


#include "./document.h"

/*! Constructor: simply initializes indexOfSelectedObject.
*/
Document::Document() {
  //indexOfSelectedObject = -1;
}

/*! Destructor: frees up the memory used up by the vector of nodes.
  @bug There is an intermitten bug where an exception will be thrown
     by .at()! (3-6-12: This hasn't happened in a long time now)
*/
Document::~Document() {
  //for (int i = 0; i < static_cast<int>(nodes.size()); i++) {
    //assert(nodes.at(i) != 0);
    // QMessageBox::information(0, "node text", nodes.at(i)->getText(),
    //                          QMessageBox::Ok, QMessageBox::Ok);
    //delete nodes.at(i);
  //}
}

/*! Slot. Updates selectedObject based on point. Uses the
  hitTest function of BaseNode. Sets to -1 if no hitTests return
  true. Also rearranges the nodes QList so that the selected object is
  the last item in the list, making it have the highest positioning order.
  @param point The point where the object should be under. Usually a mouse coordinate.
*/
void Document::setSelectedObject(const QPoint &point) {
  //assert(indexOfSelectedObject >= -1);
  //assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  // reset the selected property of previously selected node
  if (selectedObject != 0) {
    selectedObject->setSelected(false);
  }

  // find the first object with a positive hittest.
  int index = getIndexAt(point);
  if (index != -1) {
    selectedObject = nodes.at(getIndexAt(point));
  } else {
    selectedObject = 0;
  }

  if (selectedObject != 0) {
    //set the node's selected property to true
    selectedObject->setSelected(true);

    // Save the difference between where the mouse click was (point) and
    // where the actual middle of the object is. This will be used to
    // acurately move and drag the object.
    positionDelta = selectedObject->getPosition() - point;

    //move the selected object to the end of the QList so that it's order
    //is set to be on top
    //nodes.removeAll(selectedObject);
    //nodes.append(selectedObject);
  }



  // at this point a redraw is needed to show the new
  // highlighted object.
  emit modelChanged();
}

/*! Slot. Updates the prototypeID for the next object to be created.
  The signal with the ID should come from the MainWindow with the
  ID being stored in a NodeAction created by MainWindow.registerPrototype()
  @param prototypeID The ID for the prototype when it was registered with the NodeFactory.
*/
void Document::setNewObjectID(int prototypeID) {
  newObjectID = prototypeID;
}

/*! This function returns an index into the nodes vector of the topmost object
    under the point.
    @param point The point the object should be under. Usually a mouse coordinate.
    @return The index of the node under the point, -1 if no object is under the point.
*/
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
  @param point The point to move the currently selected object to.
*/
void Document::moveSelectedObject(const QPoint &point) {
  //assert(indexOfSelectedObject >= -1);
  //assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  if (selectedObject != 0) {
    selectedObject->setPosition(point + positionDelta);
  }

  emit modelChanged();
}

/*! Slot. This will create a new object at the specified position. The
  prototypeID of the new object will have been set by a previous signal
  to setNewObjectID. Uses NodeFactory.
*/
void Document::createObject(const QPoint &position) {
  //assert(indexOfSelectedObject >= -1);
  //assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  // create a new node using the factory
  BaseNode* newNode;
  newNode = NodeFactory::getInstance()->produce(newObjectID);
  newNode->setPosition(position);

  // add newnode to a vector of nodes.
  addNode(newNode);

  // reset the selected property of previously selected node
  if (selectedObject != 0) {
    selectedObject->setSelected(false);
  }

  // set the selected index to be the created object
  // (the node list will never be empty because we have at least
  //  added one item to it, so we don't have to check isEmpty(). )
  selectedObject = nodes.back();
  selectedObject->setSelected(true);

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
    if (((index != -1) &&
         (nodes.at(index)->isConnector() == false)) &&
            index != firstConnectionIndex) {
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
  //assert(indexOfSelectedObject >= -1);
  //assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  if (selectedObject != 0) {
    QDialog *properties;
    properties = selectedObject->getDialog();

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
  //assert(indexOfSelectedObject >= -1);
  //assert(indexOfSelectedObject < static_cast<int>(nodes.size()));

  if (selectedObject != 0) {
    BaseNode* obj = selectedObject;
    if (obj->isConnector() == false) {
      // erase all the connected connectionnodes
      // get the list of connected nodes, which are all connections
      std::list<BaseNode*> objs;
      objs = obj->getConnectedNodes();

      // iterate through that list and delete the connection nodes
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
      //nodes.erase(nodes.begin()+indexOfSelectedObject);
      nodes.removeAll(selectedObject);
      QMessageBox::information(0, "selected boject", selectedObject->getText());
    } else {
      // get the list of connected objects (should only be two objects)
      std::list<BaseNode*> secondaryObjects;
      secondaryObjects = obj->getConnectedNodes();

      // iterate through the list and disconnect the connectionnode we
      // are deleting from the objects.
      std::list<BaseNode*>::iterator it;  // NOLINT
      for (it = secondaryObjects.begin(); it != secondaryObjects.end(); ++it) {
        (*it)->removeConnectedNode(obj);
      }

      // now delete the actual node
      //nodes.erase(nodes.begin()+indexOfSelectedObject);
      nodes.removeAll(selectedObject);
    }
  }

  selectedObject = 0;
  emit modelChanged();
}

void Document::saveDocument() {
  // if (filename.empty)
}

void Document::saveAsDocument() {
}
