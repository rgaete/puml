/*!
 * @file diagrams.h
 *      @brief These classes describe the structure of the diagrams.
 */

#ifndef pUML_DIAGRAMS
#define pUML_DIAGRAMS

/*!
 * This is the abstract base class for all diagrams.
 */
class Diagram {
    public:
        Diagram() {}
        virtual void foo() {}
    private:
};

/*!
 * The UseCaseDiagram holds the use case UML view.
 * @sa Diagram
 */
class UseCaseDiagram:public Diagram {
    public:
        UseCaseDiagram() {}
    private:
};

/*!
 * There is only one of these objects per project. It holds references
 * to all five views. It is, in most ways, the top level object for the
 * program.
 */
class AllDiagrams {
    public:
    private:
};

#endif
