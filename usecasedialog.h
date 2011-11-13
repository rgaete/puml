#ifndef USECASEDIALOG_H
#define USECASEDIALOG_H

#include <QDialog>

class QPushButton;
class QTextEdit;
class QLabel;
class QLineEdit;
class QString;

class UseCaseDialog : public QDialog
{
    Q_OBJECT

public:
    UseCaseDialog(QWidget *parent = 0);

private:
    QPushButton *closeButton;
    QPushButton *submitButton;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QLabel *label;


private slots:
    void okClicked();

};

#endif // USECASEDIALOG_H
