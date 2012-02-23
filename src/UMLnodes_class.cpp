#include "UMLnodes_class.h"

void ClassConnection::draw(QPainter& painter)
{
    QPoint pt1, pt2, pt3, pt4;
    BaseNode *obj1, *obj2;
    list<BaseNode*>::iterator it = connectedObjects.begin();
    obj1 = *(it);
    it++;
    obj2 = *(it);

    pt1 = obj1->getClosestConnectionPoint(obj2->getPosition());
    pt4 = obj2->getClosestConnectionPoint(obj1->getPosition());

    if(pt1.x()==obj1->getPosition().x()) //North or South connection
    {

        pt2.setY((pt4.y()+pt1.y())/2);
        pt2.setX(pt1.x());
        pt3.setX(pt4.x());
        pt3.setY(pt2.y());
    }
    else if(pt1.x()!=obj1->getPosition().x()) //East or West connection
    {
        pt2.setY(pt1.y());
        pt2.setX((pt1.x()+pt4.x())/2);
        pt3.setX(pt2.x());
        pt3.setY(pt4.y());
    }
    painter.setPen(Qt::black);
    painter.drawLine(pt1, pt2);
    painter.drawLine(pt2, pt3);
    painter.drawLine(pt3, pt4);
}
