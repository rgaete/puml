// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_DIALOG_H_
#define SRC_DIALOG_H_

#include <QDialog>

#include "./nodes.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
class QLineEdit;
QT_END_NAMESPACE


class ConfigDialog : public QDialog {
  Q_OBJECT

  public:
    enum ConfigDialogType {
        OpenAndNew,
        NewOnly
    };

    ConfigDialog(ConfigDialogType type);


  public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void browseForFile();
    void accept();
    void reject();

 signals:
    void newDiagramType(BaseNode::DiagramType diagramType);
    void openDiagramFile(const QString &filename);

  private:
    void createIcons(ConfigDialogType type);
    void createNewPage();
    void createOpenPage();


    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    QListWidget *doctypeList;
    QWidget *newPage;
    QWidget *openPage;
    QLineEdit *filenameBox;
    QString fileName;
};

#endif  // SRC_DIALOG_H_
