// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_DIALOG_H_
#define SRC_DIALOG_H_

#include <QDialog>

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


  public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void browseForFile();
    void accept();

 signals:
    void newDiagramType(BaseNode::DiagramType diagramType);
    void openDiagramFile(QString filename);

  private:
    void createIcons();
    void createNewPage();
    void createOpenPage();


    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QListWidget *doctypeList;
    QWidget *newPage;
    QWidget *openPage;
    QString fileName;
};

#endif  // SRC_DIALOG_H_
