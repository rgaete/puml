// Copyright (C) 2011-2012 pUML Group


#include "./document.h"
#include <utility>
#include <vector>
#include <fstream>  // NOLINT
#include <string>

using std::ofstream;  // NOLINT
using std::vector;
using std::string;

int saveattempt;

/* This opens the specified file as a QDomDocument* or returns NULL on failure.
 */
QDomDocument* openSaveFile(QString openName) {
  QDomDocument *xmlDoc = new QDomDocument(openName);

  // Make sure that this is a readable file.
  char msg[256];
  sprintf(msg, "Couldn't open the file %s", openName.toStdString().c_str());

  QFile file(openName);
  if (!file.open(QIODevice::ReadOnly)) {
    //QMessageBox::critical(this, "Load XML File Problem", msg, QMessageBox::Ok);
    return NULL;
  }

  if (!xmlDoc->setContent(&file)) {
    //QMessageBox::critical(this, "Load XML File Problem", msg, QMessageBox::Ok);
    file.close();
    return NULL;
  }
  file.close();
  return xmlDoc;
}

/* Goal: Each call to this function generates the next document element.
 * Note: I'm not certain that this will work if more than one document node
 * is present in the XML!
 */
QDomElement getNextDocumentElement(QDomDocument* xmlDoc) {
  static QDomDocument* lastXMLSeen;
  static QDomNode currentDocument;

  if (lastXMLSeen != xmlDoc) {
    lastXMLSeen = xmlDoc;
    currentDocument = xmlDoc->firstChildElement(QString("document"));
  } else {
    currentDocument = currentDocument.nextSibling();
  }

  if (currentDocument.isNull()) {
    lastXMLSeen = NULL;
  }

  return currentDocument.toElement();
}

/* Goal: Each call to this function generates the next node element.
 */
QDomElement getNextNodeElement(QDomElement &documentElement) {
  static QDomElement* lastDocumentSeen;
  static QDomElement nodesVectorElement;
  static QDomNode currentNode;

  if (lastDocumentSeen != &documentElement) {
    // Reset the generator on a new document.
    lastDocumentSeen = &documentElement;
    nodesVectorElement = documentElement.firstChildElement(
        QString("nodes_vector_element"));
    currentNode = nodesVectorElement.firstChild();
  } else {
    // Iterate the generator to the next element if not a new document.
    currentNode = currentNode.nextSibling();
  }

  QDomElement retval = currentNode.toElement();
  if (retval.isNull()) {
    lastDocumentSeen = NULL;
  }
  return retval;
}

void experiment(QString openName) {
  fprintf(stderr, "> experiment()\n");
  QDomDocument* xmlDoc = openSaveFile(openName);
  QDomElement docElem = getNextDocumentElement(xmlDoc);
  QDomElement n;
  BaseNode* newNode;

  while (1) {
    n = getNextNodeElement(docElem);
    if (n.isNull()) {
      break;
    }

    fprintf(stderr, "Should print class_name: %-21s pos_x: %-3s pos_y: %s\n",
            qPrintable(n.attribute(QString("class_name"))),
            qPrintable(n.attribute(QString("pos_x"))),
            qPrintable(n.attribute(QString("pos_y"))));

    // what we have is a QDOMElement, and we need a node to put in the vector

    newNode = NodeFactory::getInstance()->produceFromClassName(n.attribute("class_name"));
    if (newNode == 0) {
        fprintf(stderr, "Got a null node\n");
    } else {
        fprintf(stderr, "Got a %-21s\n", newNode->metaObject()->className());
    }

  }
  fprintf(stderr, "< experiment()\n");
}

/* REMOVE ME! I AM SCAR CODE.
  // print out the element names of all elements that are direct children
  // of the outermost element.
  QDomElement docElem = xmlDoc.documentElement();

  fprintf(stderr, "!!!! %s\n", qPrintable(docElem.attribute(QString("node"))));
  QDomNode n = docElem.firstChild();
  while(!n.isNull()) {
    QDomElement e = n.toElement(); // try to convert the node to an element.
    if(!e.isNull()) {
    }
    n = n.nextSibling();
  }
*/

/*! Constructor: simply initializes indexOfSelectedObject.
*/
Document::Document() {
  indexOfSelectedObject = -1;
  fileName = "";
  modifiedFlag = false;
}

/*

xmlFile = new QFile("xmlFile.xml");
        if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::critical(this,"Load XML File Problem",
                "Couldn't open xmlfile.xml to load settings for download",
                QMessageBox::Ok);
                return;
        }
xmlReader = new QXmlStreamReader(xmlFile);


//Parse the XML until we reach end of it
while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
                continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {

                if(xmlReader->name() == "name") {
                        continue;
                }

                if(xmlReader->name() == "id") {
                    qDebug() << xmlReader->readElementText();
                }
        }
}

if(xmlReader->hasError()) {
        QMessageBox::critical(this,
        "xmlFile.xml Parse Error",xmlReader->errorString(),
        QMessageBox::Ok);
        return;
}

//close reader and flush file
xmlReader->clear();
xmlFile->close();
*/

Document::Document(QString fpath) {
  fprintf(stderr, "> Document::Document(QString fpath)\n");

  QFile* xml_file = new QFile(fpath);
  if (!xml_file->open(QIODevice::ReadOnly | QIODevice::Text)) {
    char msg[256];
    sprintf(msg, "Couldn't open the file %s",
            fpath.toStdString().c_str());
    QMessageBox::critical(this, "Load XML File Problem", msg, QMessageBox::Ok);
    return;
  }

  fprintf(stderr, "< Document::Document(QString fpath)\n");
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
    // set the selection of on the object
    nodes.at(indexOfSelectedObject)->setSelected(true);

    // Save the difference between where the mouse click was (point) and
    // where the actual middle of the object is. This will be used to
    // acurately move and drag the object.
    positionDelta = nodes.at(indexOfSelectedObject)->getPosition() - point; }

  // at this point a redraw is needed to outputshow the new
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

/*!
*/
int Document::getIndexAt(const QPoint &point) {
  int index = -1;
  for (int i = ordering.size()-1; i >= 0; i--) {
    if (nodes.at(ordering.at(i))->hitTest(point) == true) {
      index = ordering.at(i);
      break;
    }
  }

  return index;
}

/*! This private helper function removes the specified index from the
    ordering, ensuring that all indexes in the ordering
    remain valid.
    @param index The index value to remove
*/
void Document::removeFromOrdering(int index) {
  if (index > -1 && index < static_cast<int>(nodes.size())) {
    ordering.removeAll(index);
    for (int i = 0; i < ordering.size(); i++) {
      if (ordering.at(i) > index) {
        ordering.replace(i, ordering.at(i) - 1);
      }
    }
  }
}

/*! Sets the modifed flag and emits the modifed changed signal. This is so
    the tabs get updated with an asterisk to indicate if the document has been
    modified.
*/
void Document::setModified(bool modified)
{
  modifiedFlag = modified;
  emit modifiedChanged(modified);
}

/*! Tries to find and return the object specifed by the given uniqued id.
    Returns null otherwise.
*/
BaseNode *Document::findNodeById(QUuid id)
{
  std::vector<BaseNode*>::iterator it;
  for (it=nodes.begin(); it!=nodes.end(); it++) {
    if (id == (*it)->Id()) {
      return (*it);
    }
  }
  qDebug("Didn't find a node by id :(");
  return 0;
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

  setModified(true);
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
  addNodeToList(newNode);

  // add the node to the ordering
  ordering.append(nodes.size()-1);

  // reset the selected property of previously selected node
  if (indexOfSelectedObject != -1) {
    nodes.at(indexOfSelectedObject)->setSelected(false);
  }

  // set the selected index to be the created object
  indexOfSelectedObject = nodes.size()-1;
  nodes.at(indexOfSelectedObject)->setSelected(true);

  setModified(true);
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
  // set the connection point selection property, so a visual
  // aid will be drawn for the object that is selected for the
  // connection
  if (firstConnectionIndex != -1) {
    nodes.at(firstConnectionIndex)->setSelectedForConnectionPoint(true);
  }
}

/*! Slot. Sets the second point in a new connection node.
  This function actually creates the node using the NodeFactory.
  It doesn't create the node if the first or second point is invalid.
*/
void Document::createConnectionPoint2(const QPoint &point) {
  // Create the object only if a valid first object was found
  int index;
  // creates a temp object node for self connectors
  BaseNode *tempnode;
  tempnode = NodeFactory::getInstance()->produce(newObjectID);

  if (firstConnectionIndex != -1) {
    index = getIndexAt(point);
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

      addNodeToList(newNode);
      ordering.append(nodes.size()-1);

      nodes.at(index)->setSelectedForConnectionPoint(false);

      setModified(true);
      emit modelChanged();
    }
    //  Self connectors
    // And the second index was found
    else if (((index != -1) &&
         (nodes.at(index)->isConnector() == false)) &&
            (index == firstConnectionIndex) &&
             (tempnode->getText() == "Collaboration Self Line")) {

        // produce the object
      BaseNode *newNode;
      newNode = NodeFactory::getInstance()->produce(newObjectID);

      // now connect the connection to both objects, and connect the
      // objects to the connections
      newNode->addConnectedNode(nodes.at(firstConnectionIndex));
      newNode->addConnectedNode(nodes.at(index));
      nodes.at(firstConnectionIndex)->addConnectedNode(newNode);
      nodes.at(index)->addConnectedNode(newNode);

      addNodeToList(newNode);
      ordering.append(nodes.size()-1);

      nodes.at(index)->setSelectedForConnectionPoint(false);

      setModified(true);
      emit modelChanged();
    }
// end of  self connect
    else {
      QMessageBox::information(0, "pUML", "No second object selected");
    }
  }

  if (firstConnectionIndex != -1) {
    nodes.at(firstConnectionIndex)->setSelectedForConnectionPoint(false);
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

    if (properties != 0) {
      properties->exec();
      delete properties;
    }
  }

  setModified(true);
  emit modelChanged();
}

/*! Slot. This will draw the nodes using painter. It assumes
  that painter is a valid painter, and uses BaseNode.draw().
*/
void Document::drawList(QPainter &painter) {  // NOLINT
  for (int i = 0; i < ordering.size(); i++) {
    if (nodes.at(ordering.at(i)) == 0) {
      qDebug() << "Drawing error: Ordering points to null node";
    } else {
      nodes.at(ordering.at(i))->draw(painter);
    }
  }
}

/*! Slot. Removes the currently selected node. If the node is
    an object, it also removes all connections connected to that
    node.
*/
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
            removeFromOrdering(i);
            nodes.erase(nodes.begin()+i);
          }
        }
      }
      // now actually erase the object
      removeFromOrdering(indexOfSelectedObject);
      nodes.erase(nodes.begin()+indexOfSelectedObject);
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

      // now delete the actual nodecount
      removeFromOrdering(indexOfSelectedObject);
      nodes.erase(nodes.begin()+indexOfSelectedObject);
    }
  }
  setModified(true);
  indexOfSelectedObject = -1;
  emit modelChanged();
}

/*! If an object is selected, this slot will move that object's
    ordering to the front of everything. Nothing will happen if
    it's at the front of everything.
*/
void Document::sendSelectedToFront() {
  if ((indexOfSelectedObject > -1 )
      && (indexOfSelectedObject < static_cast<int>(nodes.size()))) {
    ordering.removeAll(indexOfSelectedObject);
    ordering.append(indexOfSelectedObject);
  }
  setModified(true);
  emit modelChanged();
}

/*! If an object is selected, this slot will move that object's
    ordering up on position. Nothing will happen if that object is
    already at the top of the ordering.
*/
void Document::sendSelectedForward() {
  if ((indexOfSelectedObject > -1)
      && (indexOfSelectedObject < static_cast<int>(nodes.size()))) {
    int orderingindex = ordering.indexOf(indexOfSelectedObject);
    if (orderingindex < ordering.size()-1) {
      ordering.move(orderingindex, orderingindex+1);
    }
  }
  setModified(true);
  emit modelChanged();
}

/*! If an object is selected, this slot will move that object's
    ordering to the back of everything. Nothing will happen if it's already
    at the back.
*/
void Document::sendSelectedToBack() {
  if ((indexOfSelectedObject > -1)
      && (indexOfSelectedObject < static_cast<int>(nodes.size()))) {
    ordering.removeAll(indexOfSelectedObject);
    ordering.prepend(indexOfSelectedObject);
  }
  setModified(true);
  emit modelChanged();
}

/*! If an object is selected, this slot will move that object's
    ordering back one spot. Nothing will happen if it's already at the back.
*/
void Document::sendSelectedBackwards() {
  if ((indexOfSelectedObject > -1)
      && (indexOfSelectedObject < static_cast<int>(nodes.size()))) {
    int orderingindex = ordering.indexOf(indexOfSelectedObject);
    if (orderingindex > 0) {
      ordering.move(orderingindex, orderingindex-1);
    }
  }
  setModified(true);
  emit modelChanged();
}

/*!
*/
void Document::changeSecondConnectionPointHint(const QPoint &point) {
  // reset the cpSelection for the previous selected node
  if ((secondConnectionIndex > -1)
      && (secondConnectionIndex < static_cast<int>(nodes.size()))) {
    if (secondConnectionIndex != firstConnectionIndex) {
      nodes.at(secondConnectionIndex)->setSelectedForConnectionPoint(false);
    }
  }

  if (firstConnectionIndex != -1) {
    // find the new node, if any
    secondConnectionIndex = getIndexAt(point);
    if (secondConnectionIndex != -1) {
      nodes.at(secondConnectionIndex)->setSelectedForConnectionPoint(true);
    }
  }
}

/*! Saves the document to a file. The file is specified by the fileName
    member variable. If the member variable isn't set, the function exits.
    If the file is an invalid file, the function produces an error message
    to the user. This function shouldn't ever be called when the filename
    isn't set.
*/
void Document::saveDocument() {
  if (this->hasFilename() != false) {
    QMessageBox::information(this, "pUML", "Trying to open file " + fileName + " for saving");
    QFile file(fileName);
    QDomDocument xml_doc("pUML_save_document");
    QDomElement documentElement = xml_doc.createElement("document");
    documentElement.setAttribute("diagramType", diagramType);
    xml_doc.appendChild(documentElement);
    QDomElement nodesElement = xml_doc.createElement("nodes_vector_element");
    documentElement.appendChild(nodesElement);

    for (vector<BaseNode*>::iterator it = nodes.begin();
         it != nodes.end(); ++it) {
      (*it)->to_xml(xml_doc, nodesElement);
    }

    // Checks to make sure that the file is writable.
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
                                 file.errorString());
        return;
    }

    ofstream myfile;
    myfile.open(fileName.toStdString().c_str());
    myfile << xml_doc.toString().toStdString();
    myfile.close();

    setModified(false);
  } else {
    qDebug() << "Document::saveDocument Error: No filename to save to!";
  }
}

/*! Opens specified file. This function does not ask the user to save an
    unsaved modified diagram. That is the MainWindow's job. This function
    will simply clear out the node vector and load the file in.
*/
void Document::openDocument(QString openName)
{
    QDomDocument* xmlDoc = openSaveFile(openName);
    QDomElement docElem = getNextDocumentElement(xmlDoc);
    QDomElement nodesVectorElement;
    QDomElement n;
    BaseNode* newNode;

    // Clear the nodes vector
    nodes.clear();
    ordering.clear();

    // Get the diagram type
    diagramType = static_cast<BaseNode::DiagramType>(docElem.attribute("diagramType").toInt());

    // First get out the first (and hopefully only) nodes_vector_element.
    nodesVectorElement = docElem.firstChildElement("nodes_vector_element");

    // Now we have to iterate over all the Node elements and restor them.
    // This style of iteration loop was taken from the Qt documentation for
    // QDomElement.
    n = nodesVectorElement.firstChildElement("Node");
    for (; !n.isNull(); n = n.nextSiblingElement("Node")) {
      // Now that we have the QDomElement, try to produce the node
      newNode = NodeFactory::getInstance()->produceFromClassName(n.attribute("class_name"));

      // Check we failed
      if (newNode == 0) {
        qDebug() << "Document::openDocument Error: Couldn't produce a " << n.attribute("class_name") << " with the node factory.";
      } else {
        // Restore the unique id and all the properties
        newNode->from_xml(n);

        // Push the node onto the node vector
        nodes.push_back(newNode);
        ordering.push_back(nodes.size()-1);
      }
    }

    // Now that we have all the id's restored, we can restore the connections
    // between the nodes. We loop over all the Node elements in
    // node_vector_element and loop over all the ConnectedObject elements in
    // each Node.
    n = nodesVectorElement.firstChildElement("Node");
    for (; !n.isNull(); n = n.nextSiblingElement("Node")) {
      BaseNode* sourcenode;
      QUuid sourceid;

      // Find the node that we created earlier from this element
      sourceid = QUuid(n.attribute("Id"));
      sourcenode = this->findNodeById(sourceid);

      if (sourcenode == 0) {
        qDebug() << "Document::openDocument Error: Couldn't find source node by id";
      } else {
        QUuid targetid;
        BaseNode* targetnode;

        // Now that we have the element and it's associated node, iterate
        // over all of the element's children ("ConnectedObjects")
        QDomElement child = n.firstChildElement("ConnectedObject");
        for (; !child.isNull(); child = child.nextSiblingElement("ConnectedObject")) {
          // Find the targeted node by id
          targetid = QUuid(child.attribute("id"));
          targetnode = this->findNodeById(targetid);

          // Check if it failed
          if (targetnode == 0) {
            qDebug() << "Document::openDocument Error: Couldn't find a target node by id";
          } else {
            // If it didn't fail, add the connection!
            sourcenode->addConnectedNode(targetnode);
          }
        }
      }
    }

    setFilename(openName);
    setModified(false);
    update();
}
