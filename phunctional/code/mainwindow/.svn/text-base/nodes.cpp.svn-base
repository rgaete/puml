/*!
 * @file nodes.cpp
 *      @brief describes the behavior of the node classes
 */

#include "nodes.h"

/*
bool BaseNode::valid_in(Diagram diagram) {
    cerr << "Invalid call -> BaseNode::valid_in()" << endl;
    return false;
}

int BaseNode::id(string shape) {
    return id_int;
}
*/

/*!
 * Registers the node in the valid_nodes global object.
 */
/*BaseNode::BaseNode() {
    valid_nodes.register_node(this);
}*/

/*ObjectNode::ObjectNode()
           :BaseNode() {
}

StickPerson::StickPerson()
            :ObjectNode() {
}*/

Oval::Oval()
     :ObjectNode() {
}

void StickPerson::test_msg() {
    cout << "StickPerson::test_msg() --" << endl;
}

void Oval::test_msg() {
    cout << "Oval::test_msg() --" << endl;
}

void StickPerson::draw(QPainter &painter)
{
    //drawing a stickperson

}

void Oval::draw(QPainter &painter)
{
    //drawing an oval
    double tempx = centerx;
    double tempy = centery;
    double tempr = radius;
    //double blank = 0;

    painter.setPen(QColor("black"));
    //obj.WindowtoViewPort(tempx, tempy);
    //obj.WindowtoViewPort(tempr, blank);
    QPoint point(tempx, tempy);

    painter.drawEllipse(point,tempr, tempr);
}
