#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <QMenu>
#include "nodes.h"

class Canvas : public QWidget
{
    Q_OBJECT
public:
    enum DrawingMode {
        Object,
        Connection,
        Nothing
    };

private:
    DrawingMode drawingMode;

    QMenu *menuPopup;
    QAction *actionDelete;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionProperties;
public:
    explicit Canvas(QWidget *parent = 0);
    QSize sizeHint() const;
    void setMode(DrawingMode mode);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

signals:
    void objectSelectionChange(const QPoint &point);
    void moveSelectedObject(const QPoint &point);
    void createObject(const QPoint &point);
    void redraw(QPainter &painter);
    void showPropertiesDialog();

public slots:
    void on_actionDelete_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionProperties_triggered();
};

#endif // CANVAS_H
