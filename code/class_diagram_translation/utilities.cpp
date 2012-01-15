/*!
 * @file utilities.cpp
 *      @brief defines utility functions
 */

#include "utilities.h"

/*!
 * @param to_print
 *      Prints the message.
 */
void debug(string to_print) {
#ifdef PRINT_DEBUG_MESSAGES
    cerr << to_print << endl;
#endif
}
