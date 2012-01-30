#ifndef ACTORDIALOG_H
#define ACTORDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class ActorDialog : public QDialog
{
    Q_OBJECT

public:
    ActorDialog(QWidget *parent = 0);

signals:

private slots:

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *acceptButton;
    QPushButton *closeButton;
};

#endif // ACTORDIALOG_H
