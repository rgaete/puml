// Copyright (C) 2011-2012 pUML Group

/*! @file UMlnodes_class.h
    @brief Defines concrete Objectnodes and Connectionnodes that specific to
           class diagrams.
  */
#ifndef SRC_UMLNODES_CLASS_H_
#define SRC_UMLNODES_CLASS_H_

#include <QInputDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QtXml>
#include "./nodes.h"
// #include "ui_ClassBoxdialog.h"


/*! @brief This defines a custom dialog for a ClassBoxObject
*/
class ClassBoxObjectDialog : public QDialog {
  Q_OBJECT

  public:
    explicit ClassBoxObjectDialog(QWidget *parent = 0);
    void setClassName(QString newClassName);
    void setAttributes(QString newAttributes);
    void setMethods(QString newMethods);
  private slots:
    void okButtonClicked();
  signals:
    void classNameSet(QString newClassName);
    void attributesSet(QString newAttributes);
    void methodsSet(QString newMethods);
  private:
    QLabel *ClassNameLabel;
    QLabel *AttributesLabel;
    QLabel *MethodsLabel;
    QLineEdit *ClassNameLineEdit;
    QTextEdit *AttributesLineEdit;
    QTextEdit *MethodsLineEdit;
    QPushButton *okButton;
};

/*!
 * @brief This concrete class is the ClassBox node.
 * @sa ObjectNode
 */
class ClassBoxObject: public ObjectNode {
  Q_OBJECT
  Q_PROPERTY(QString methods READ methods WRITE setMethods)
  Q_PROPERTY(QString className READ className WRITE setClassName)
  Q_PROPERTY(QString attributes READ attributes WRITE setAttributes)

  public:
    ClassBoxObject();
    // QDomElement to_xml(QDomDocument &doc, QDomElement &doc_root);
    BaseNode* clone() { return new ClassBoxObject; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/class.png"); }
    QString getText() { return "ClassBox"; }
    DiagramType getDiagramType() { return Class; }
    void draw(QPainter &painter);  // NOLINT

    QString methods() const { return m_methods; }
    QString attributes() const { return m_attributes; }
    QString className() const { return m_className; }

  public slots:
    void setClassName(QString newClassName) {
      this->m_className = newClassName;
    }
    void setAttributes(QString newAttributes) {
      this->m_attributes = newAttributes;
    }
    void setMethods(QString newMethods) {
      this->m_methods = newMethods;
    }

  private:
    int classHeight;
    int attributeHeight;
    int methodHeight;
    QString m_className;
    QString m_attributes;
    QString m_methods;
};


/*! @brief This concrete class defines ...
 */
class ClassConnection : public SquareConnectionNode {
  Q_OBJECT
  Q_PROPERTY(QString start READ getStart WRITE setStart)
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString end READ getEnd WRITE setEnd)

  public:
    BaseNode* clone() { return new ClassConnection; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Association"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Class; }

    QString getStart() { return m_start; }
    QString getName() { return m_name; }
    QString getEnd() { return m_end; }
public slots:
   void setStart(QString newStart) { this->m_start = newStart; }
   void setName(QString newName) { this->m_name = newName; }
   void setEnd(QString newEnd) { this->m_end = newEnd; }
private:
    double lineAngle;
    QString m_start;
    QString m_name;
    QString m_end;
};

/*! @brief The properties dialog for class connections
 */
class ClassConnectionDialog : public QDialog {
    Q_OBJECT

public:
   explicit ClassConnectionDialog(QWidget *parent = 0);
   void setStart(QString newStart);
   void setName(QString newName);
   void setEnd(QString newEnd);
private slots:
   void okButtonClicked();
signals:
   void startSet(QString newStart);
   void nameSet(QString newName);
   void endSet(QString newEnd);
private:
   QLabel *StartLabel;
   QLabel *NameLabel;
   QLabel *EndLabel;
   QLineEdit *StartLineEdit;
   QLineEdit *NameLineEdit;
   QLineEdit *EndLineEdit;
   QPushButton *okButton;
};


class InheritanceConnection : public SquareConnectionNode {
  Q_OBJECT
  Q_PROPERTY(QString start READ getStart WRITE setStart)
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString end READ getEnd WRITE setEnd)

public:
    BaseNode* clone() { return new InheritanceConnection; }
    QDialog* getDialog();
    QString getIconPath() { return QString(":/Images/interaction.png"); }
    QString getText() { return "Inheritance Line"; }
    void draw(QPainter& painter);  // NOLINT
    DiagramType getDiagramType() { return Class; }
    void addArrow(QPainter& painter);

    QString getStart() { return m_start; }
    QString getName() { return m_name; }
    QString getEnd() { return m_end; }
public slots:
   void setStart(QString newStart) { this->m_start = newStart; }
   void setName(QString newName) { this->m_name = newName; }
   void setEnd(QString newEnd) { this->m_end = newEnd; }
private:
    double lineAngle;
    QString m_start;
    QString m_name;
    QString m_end;
};

class InheritanceConnectionDialog : public QDialog {
    Q_OBJECT

public:
   explicit InheritanceConnectionDialog(QWidget *parent = 0);
   void setStart(QString newStart);
   void setName(QString newName);
   void setEnd(QString newEnd);
private slots:
   void okButtonClicked();
signals:
   void startSet(QString newStart);
   void nameSet(QString newName);
   void endSet(QString newEnd);
private:
   QLabel *StartLabel;
   QLabel *NameLabel;
   QLabel *EndLabel;
   QLineEdit *StartLineEdit;
   QLineEdit *NameLineEdit;
   QLineEdit *EndLineEdit;
   QPushButton *okButton;
};

class AggregationConnection : public SquareConnectionNode {
  Q_OBJECT
  Q_PROPERTY(QString start READ getStart WRITE setStart)
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString end READ getEnd WRITE setEnd)

public:
  BaseNode* clone() { return new AggregationConnection; }
  QDialog* getDialog();
  QString getIconPath() { return QString(":/Images/interaction.png"); }
  QString getText() { return "Aggregation Line"; }
  void draw(QPainter& painter);  // NOLINT
  DiagramType getDiagramType() { return Class; }

  QString getStart() { return m_start; }
  QString getName() { return m_name; }
  QString getEnd() { return m_end; }
public slots:
  void setStart(QString newStart) { this->m_start = newStart; }
  void setName(QString newName) {  this->m_name = newName; }
  void setEnd(QString newEnd) { this->m_end = newEnd; }
private:
  double lineAngle;
  QString m_start;
  QString m_name;
  QString m_end;
};

/*! @brief The properties dialog for class connections
 */
class AggregationConnectionDialog : public QDialog {
    Q_OBJECT

public:
   explicit AggregationConnectionDialog(QWidget *parent = 0);
   void setStart(QString newStart);
   void setName(QString newName);
   void setEnd(QString newEnd);
private slots:
   void okButtonClicked();
signals:
   void startSet(QString newStart);
   void nameSet(QString newName);
   void endSet(QString newEnd);
private:
   QLabel *StartLabel;
   QLabel *NameLabel;
   QLabel *EndLabel;
   QLineEdit *StartLineEdit;
   QLineEdit *NameLineEdit;
   QLineEdit *EndLineEdit;
   QPushButton *okButton;
};



class CompositionConnection : public SquareConnectionNode {
  Q_OBJECT
  Q_PROPERTY(QString start READ getStart WRITE setStart)
  Q_PROPERTY(QString name READ getName WRITE setName)
  Q_PROPERTY(QString end READ getEnd WRITE setEnd)

public:
  BaseNode* clone() { return new CompositionConnection; }
  QDialog* getDialog();
  QString getIconPath() { return QString(":/Images/interaction.png"); }
  QString getText() { return "Composition Line"; }
  void draw(QPainter& painter);  // NOLINT
  DiagramType getDiagramType() { return Class; }

  QString getStart() { return m_start; }
  QString getName() { return m_name; }
  QString getEnd() { return m_end; }
public slots:
  void setStart(QString newStart) { this->m_start = newStart; }
  void setName(QString newName) {  this->m_name = newName; }
  void setEnd(QString newEnd) { this->m_end = newEnd; }
private:
  double lineAngle;
  QString m_start;
  QString m_name;
  QString m_end;
};

/*! @brief The properties dialog for class connections
 */
class CompositionConnectionDialog : public QDialog {
    Q_OBJECT

public:
   explicit CompositionConnectionDialog(QWidget *parent = 0);
   void setStart(QString newStart);
   void setName(QString newName);
   void setEnd(QString newEnd);
private slots:
   void okButtonClicked();
signals:
   void startSet(QString newStart);
   void nameSet(QString newName);
   void endSet(QString newEnd);
private:
   QLabel *StartLabel;
   QLabel *NameLabel;
   QLabel *EndLabel;
   QLineEdit *StartLineEdit;
   QLineEdit *NameLineEdit;
   QLineEdit *EndLineEdit;
   QPushButton *okButton;
};
#endif  // SRC_UMLNODES_CLASS_H_
