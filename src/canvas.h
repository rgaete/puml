// Copyright (C) 2011-2012 pUML Group

#ifndef SRC_CANVAS_H_
#define SRC_CANVAS_H_

#include <QWidget>
#include <QTableWidget>
#include <QMenu>
#include <QMouseEvent>

#include <vector>

#include "./nodes.h"

class Canvas : public QWidget {
  Q_OBJECT

  public:
    enum DrawingMode {
        Object,
        Connection,
        Nothing
    };

  private:
    // The mode the canvas is in, which determines what happens at mouse events
    DrawingMode drawingMode;
    // The index of the currently connected document
    int documentIndex;
    // The first point of the line hint
    QPoint lineHint1;
    // The second point of the line hint
    QPoint lineHint2;
    // True -> draw the line hint, false -> don't draw it.
    bool drawLineHint;

    // The context menu
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
    DrawingMode getMode() { return drawingMode; }
    int getDocumentIndex() { return documentIndex; }
    void setDocumentIndex(int docIndex) { documentIndex = docIndex; }

  protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);  // NOLINT
    void mouseMoveEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

  signals:
    void objectSelectionChange(const QPoint &point);
    void moveSelectedObject(const QPoint &point);
    void createObject(const QPoint &point);
    void createConnectionPoint1(const QPoint &point);
    void createConnectionPoint2(const QPoint &point);
    void redraw(QPainter &painter);  // NOLINT
    void showPropertiesDialog();
    void removeObject();
    void changeSecondConnectionPointHint(const QPoint &point);
    // void selectNothing();

  public slots:
    void on_actionDelete_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionProperties_triggered();
};

#endif  // SRC_CANVAS_H_
