#ifndef DIALOGNEW_H
#define DIALOGNEW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

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

class DialogNew : public QDialog
{
    Q_OBJECT
public:
    explicit DialogNew(QWidget *parent = 0);
    enum DiagramType {
        UseCase,
        Class,
        Interaction,
        State,
        Activity
    };

    DiagramType getDiagramType();
signals:

public slots:
    void on_OkButton_accepted();
    void on_UseCaseRadioButton_clicked();
    void on_ClassRadioButton_clicked();
    void on_ActivityRadioButton_clicked();
    void on_InteractionRadioButton_clicked();
    void on_StateRadioButton_clicked();

private:
    DiagramType diagramType;

};

#endif // DIALOGNEW_H
