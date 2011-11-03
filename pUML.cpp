/*!
 * @file pUML.cpp
 *      @brief launch point for program
 */

#include "pUML.h"

int main(int argc, char** argv) {
    // Empty array with two elements... for testing
    BaseNode** nodes = (BaseNode**)malloc(sizeof(BaseNode*) * 2);

    StickPerson stick;
    Oval oval;
    nodes[0] = &stick;
    nodes[1] = &oval;

    for (int i = 0 ; i < 2 ; i++) {
        nodes[i] -> test_msg();
    }

    stick.test_msg();

    return 0;
}
