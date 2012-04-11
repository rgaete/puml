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

/*! Constructor: simply initializes indexOfSelectedObject.
*/
Document::Document() {
  indexOfSelectedObject = -1;
}

/*vector<QXmlStreamReader::TokenType>*/ void pre_parse_nodes_vector(
    QXmlStreamReader* xml_reader) {

  while (!xml_reader->atEnd() && !xml_reader->hasError()) {
    QXmlStreamReader::TokenType token = xml_reader->readNext();
    fprintf(stderr, "Hey, Sponge Bob, I saw this! %s\n",
            xml_reader->name().toString().toStdString().c_str());
  }

  //return NULL;
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

  QXmlStreamReader* xml_reader = new QXmlStreamReader(xml_file);

  pre_parse_nodes_vector(xml_reader);

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

/*! This helper function removes the specified index from the
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

  emit modelChanged();
}

/*! Slot. This will draw the nodes using painter. It assumes
  that painter is a valid painter, and uses BaseNode.draw().
*/
void Document::drawList(QPainter &painter) {  // NOLINT
  for (int i = 0; i < ordering.size(); i++) {
    nodes.at(ordering.at(i))->draw(painter);
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
  emit modelChanged();
}

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

void Document::saveDocument() {
  string documentName;

  // Simple converstion for C string check.
  documentName = fileName.toStdString().c_str();
  // Verifies that the filename specified is a valid one.
  if (documentName.empty() && saveattempt == 0) {
    // If a filename and path doesn't exist it forces it to the saveas routine
    // to get the filename.
    Document::saveAsDocument();
  } else if (documentName.empty() && saveattempt >= 1) {
    saveattempt = 0;
    return;
  } else {
    QFile file(fileName);
    QDomDocument xml_doc("nodes_vector_xml");
    QDomElement root = xml_doc.createElement("nodes_vector_xml");
    xml_doc.appendChild(root);

    for (vector<BaseNode*>::iterator it = nodes.begin();
         it != nodes.end(); ++it) {
      (*it)->to_xml(xml_doc, root);
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
    //  write the saving as file function here with the fileName
  }
}


void Document::saveAsDocument() {
    saveattempt++;
    // Saves file name to current document only accesible variable.
    fileName = QFileDialog::getSaveFileName(this, tr("Save As File"),
                                            tr("XML files (*.xml)"));
    // Need to add if canceled saving a name it will stop the loop, as its currently infinite.
    Document::saveDocument();
}
