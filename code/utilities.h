/*!
 * @file utilities.h
 *      @brief declares utility functions
 */

#ifndef pUML_UTILITIES
#define pUML_UTILITIES

#include <string.h>
#include <iostream>

#include "constants.h"

using namespace std;

// Replace with Q_rect?
// x[0], y[0] is top left of rectangle
// x[1], y[1] is bottom right of rectangle
typedef struct rect {
    int x[2];
    int y[2];
} rect;

void debug(string to_print);

#endif
