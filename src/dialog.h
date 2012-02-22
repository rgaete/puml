#ifndef DIALOGUE_H
#define DIALOGUE_H

#include <QDialog>

#include "dialog.h"
#include "dialogpages.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class ConfigDialog : public QDialog
{
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

private:
    void createIcons();


    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
};

#endif // DIALOGUE_H

