// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_DIALOG_H_
#define SRC_DIALOG_H_

#include <QDialog>

#include "./dialog.h"
#include "./dialogpages.h"
#include "./nodes.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class ConfigDialog : public QDialog {
  Q_OBJECT

  public:
    ConfigDialog();
    CreateNewPage *Newpage;
    CreateOpenPage *Openpage;

  public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void CloseDialog();
    void AcceptValue(int diagramenum);
    void accepted();

 signals:
    void newDiagramType(ObjectNode::DiagramType diagramType);

  private:
    void createIcons();
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif  // SRC_DIALOG_H_
