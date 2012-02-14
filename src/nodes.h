/*!
 * @file nodes.h
 *      @brief describes the heirarchy and structure of the node classes.
               This is a copy put into the main Creator project, to be
               updated with the current class diagrams. -Josh 12/4
 */

#ifndef pUML_NODES
#define pUML_NODES

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <QRect>
#include <QPainter>
#include <QAction>
#include <list>
#include "math.h"

//#include "utilities.h"
//#include "diagrams.h"

using namespace std;

class BaseNode;


/*!
 * This defines the generic drawable object, which includes connectors (arrows and the like)
 * and objects (such as a stick person or a state oval).
 */
class BaseNode : public QObject {
    public:
        BaseNode();
        //~BaseNode() {}

        void setSelected(bool newState) { selected = newState; }
        void setPosition(const QPoint &pos) { position = pos; setUpConnectionPoints();}
        void setPoints(const QPoint &p1, const QPoint &p2) { point1=p1; point2=p2; }
        QPoint getPosition() { return position; }

        virtual void draw(QPainter &painter) =0;
        virtual BaseNode* clone() =0;
        virtual QDialog* getDialog() =0;
        virtual QString getIconPath() =0;
        virtual QString getText() =0;
        virtual bool hitTest(const QPoint &point) =0;
        virtual bool isConnector() =0;


        void addConnnectionPoint(const QPoint &newpoint);
        void addConnectedNode(BaseNode *newObject);
        void removeConnectedNode(BaseNode *object);
        QPoint getClosestConnectionPoint(const QPoint& point);
        list<BaseNode*> getConnectedNodes();



    private:
        vector<QPoint> connectionPoints;

    protected:
        virtual void setUpConnectionPoints();

        bool selected;
        QPoint position;
        QPoint point1;
        QPoint point2;
        //! The length (i.e. width) of the bounding box for this object
        int length;
        //! The height of the bounding box for this object
        int height;
        list<BaseNode*> connectedObjects;
};

/*!
 * @class ObjectNode
 * @brief This is the base class for all object nodes.
 * @sa BaseNode
 *
 * All objects should inherit from this class, while all
 * connection should inherit from @see ConnectionNode.
 * This function defines only two of the virtual methods
 * inherited from BaseNode, the rest need to be defined by
 * derived classes.
 */
class ObjectNode: public BaseNode {
    Q_OBJECT
public:
    /*! ObjectNode constructor, set the position.
     *  @param position The center of the object, relative to the containing widget.
     */
    ObjectNode();

    /*! This function performs a simple hittest by test whether
     *  the specified point is inside the box defined by the
     *  @see position, @see length, and @see height.
     *  @param point The point to hittest at, relative to the canvas widget.
     */
    bool hitTest(const QPoint &point);

    /*! This function draws selection boxes at the corners
     *  defined by @see length and @see height.
     *  @param painter A valid QPainter passed by the containing widget.
     */
    void draw(QPainter &painter);

    /*!
     *
     */
    bool isConnector() { return false; }

protected:


};

/*!
 * This abstract base class describes the connection nodes.
 * Note that even though this class has pointer members,
 * it does not a special copy constructor, assignment operator or
 * destructor for them.
 * @sa BaseNode
 */

class ConnectionNode: public BaseNode {
public:
    //void setPoints(const QPoint &point1, const QPoint &point2);

    //virtual BaseNode* factory();
    //bool hitTest(int x, int y);
    bool isConnector() { return true; }

protected:
};

#endif
