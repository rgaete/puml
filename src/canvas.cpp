// Copyright (C) 2011-2012 pUML Group

#include "./canvas.h"
#include <QMessageBox>

/*! Constructor for the canvas. It sets the sizing policy,
  sets the background to white, and sets the
  whatToDrawNext variable to Nothing.
  */
Canvas::Canvas(QWidget *parent)
       :QWidget(parent) {
  // Set the size policy to say that sizeHint() is a recomended
  // minimum, but the widget should take up all space available,
  // and the widget can also be smaller than the sizeHint().
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  //setFocusPolicy(Qt::StrongFocus);

  QShortcut *deleteKey = new QShortcut(QKeySequence(Qt::Key_Delete), this);
  connect(deleteKey, SIGNAL(activated()), this, SIGNAL(removeObject()));

  // Set the background to white. This is done by setting the
  // background role of a new palette to white, and then setting
  // that palette to this widget. This way the background color
  // is painted before the paintevent is called
  setAutoFillBackground(true);
  QPalette newPalette(palette());
  newPalette.setColor(QPalette::Window, Qt::white);
  setPalette(newPalette);

  // Initialize typeOfNewObject
  drawingMode = Nothing;

  // Create the actions
  actionDelete = new QAction(this);
  actionDelete->setText("Delete");
  actionDelete->setShortcut(Qt::Key_Delete);
  actionCut = new QAction(this);
  actionCut->setText("Cut");
  actionCut->setEnabled(false);
  actionCopy = new QAction(this);
  actionCopy->setText("Copy");
  actionCopy->setEnabled(false);
  actionPaste = new QAction(this);
  actionPaste->setText("Paste");
  actionPaste->setEnabled(false);
  actionProperties = new QAction(this);
  actionProperties->setText("Properties");
  connect(actionDelete, SIGNAL(triggered()),
          this, SLOT(on_actionDelete_triggered()));
  connect(actionCut, SIGNAL(triggered()),
          this, SLOT(on_actionCut_triggered()));
  connect(actionCopy, SIGNAL(triggered()),
          this, SLOT(on_actionCopy_triggered()));
  connect(actionPaste, SIGNAL(triggered()),
          this, SLOT(on_actionPaste_triggered()));
  connect(actionProperties, SIGNAL(triggered()),
          this, SLOT(on_actionProperties_triggered()));

  menuPopup = new QMenu(this);
  menuPopup->addAction(actionCut);
  menuPopup->addAction(actionCopy);
  menuPopup->addAction(actionPaste);
  menuPopup->addAction(actionDelete);
  menuPopup->addAction(actionProperties);

  // setContextMenuPolicy(Qt::CustomContextMenu);
}

/*! sizeHint: returns a recomended size, used by layouts. */
QSize Canvas::sizeHint() const {
  return QSize(50, 50);
}

/*! This function is called when you want to set
  what type of object the canvas is going to
  draw next.
*/
void Canvas::setMode(DrawingMode mode) {
  drawingMode = mode;
  // QMessageBox::information(0, "setMode: mode",
  //                          QString::number((int)drawingMode),
  //                          QMessageBox::Ok);
}

/*! This function paints the canvas. That means it
  draws the background grid and then calls drawList.
  @todo Update the grid settings using some sort of user preference
*/
void Canvas::paintEvent(QPaintEvent * /*event*/) {  // NOLINT
  QPainter painter(this);

  /* Draw a grid. Shamelessly stolen from a previous
   * assignment. */
  /* Update with stored preferences, zoom level */
  int lineThickness = 1;
  QColor lineColor = QColor(245, 245, 245, 255);
  int colWidth = 10;
  int rowHeight = 10;

  // set up the pen using the preferences
  QPen pen;
  pen.setWidth(lineThickness);
  pen.setColor(lineColor);
//  pen.setStyle(Qt::DotLine);
  painter.setPen(pen);

  // Create two vectors of lines, then use drawLines
  // to draw them
  QVector<QLine> hlines;
  QVector<QLine> vlines;
  int vlinescount = width()/colWidth + 1;
  int hlinescount = height()/rowHeight + 1;
  for (int i = 0; i < vlinescount; i++) {
    vlines.push_back(QLine(i*colWidth, 0, i*colWidth, hlinescount*rowHeight));
  }
  for (int i = 0; i < hlinescount; i++) {
    hlines.push_back(QLine(0, i*rowHeight,
                           vlinescount*colWidth, i*rowHeight));
  }
  painter.drawLines(hlines);
  painter.drawLines(vlines);

  // draw the line hint for connections if need be
  if (drawLineHint == true) {
    pen.setWidth(2);
    pen.setColor(Qt::blue);
    painter.setPen(pen);
    painter.drawLine(lineHint1, lineHint2);
  }

  // Draw the nodes!!!
  // Emit a draw signal
  emit redraw(painter);

  // Kill the painter
  painter.end();
}

/*! This event occures when the user presses down on the
  the mouse but hasn't release it yet. Here is where
  we want to select objects to start dragging them and find
  the first objects for connections.
*/
void Canvas::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    switch (drawingMode) {
    case Object:
      // The object is actually created in the release event, although
      // in Object mode we want to be able to select objects and move them,
      // so we emit selection change here, so objects can get selected.
      emit objectSelectionChange(event->pos());
      break;
    case Connection:
      // let the document know what the first point was
      // The document will work out what to connect to.
      emit createConnectionPoint1(event->pos());
      // start drawing the line hint
      drawLineHint = true;
      lineHint1 = event->pos();
      lineHint2 = event->pos();
      update();
      break;
    case Nothing:
      // let the document know that the user is selecting at this position.
      emit objectSelectionChange(event->pos());
      break;
    }
  }
}

/*! In the mouseMoveEvent of the canvas, an object
  will be moved if the canvas is in selection or object mode.
*/
void Canvas::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() = Qt::LeftButton) {
    switch (drawingMode) {
    case Nothing:
      // The user is moving the mouse while holding down
      // the left mouse button, and the canvas is in
      // selection mode, they must be dragging!
      emit moveSelectedObject(this->mapFromGlobal(event->globalPos()));
      break;
    case Connection:
      // update the second line hint point
      lineHint2 = this->mapFromGlobal(event->globalPos());
      emit changeSecondConnectionPointHint(
            this->mapFromGlobal(event->globalPos()));
      update();
      break;
    case Object:
      // We want to drag the object even in Object mode, if there is an
      // object selected.
      emit moveSelectedObject(this->mapFromGlobal(event->globalPos()));
      break;
    }
  }
}

/*! This function will do various things based on
  what whatToDrawNext is set to. It can create
  objects and connections, select objects, etc.
*/
void Canvas::mouseReleaseEvent(QMouseEvent *event) {
  // QMessageBox::information(0, "pUML", QString::number((int)drawingMode),
  //                          QMessageBox::Ok);
    QPoint position(0,0);
  if (event->button() == Qt::LeftButton) {
    switch (drawingMode) {
    case Object:
      // let the document know to create an object at this position.
      emit createObject(event->pos());
      // The document will automatically pop up the properties dialog and
      // select the new object.
      break;
    case Connection:
      // let the document know this is the second connection position.
      emit createConnectionPoint2(event->pos());
      // stop drawing the line hint
      drawLineHint = false;
      update();
      emit objectSelectionChange(position);
      break;
    case Nothing:
      // no defined behavior
      break;
    }
  }
}

/*! This function is called when the widget thinks that
  a context menu is needed. E.g., the right mouse
  button is clicked or the menu button is pressed.
*/
void Canvas::contextMenuEvent(QContextMenuEvent *event) {
  // select what's the under the mouse
  emit objectSelectionChange(event->pos());
  // popup the menu at the current mouse position
  menuPopup->exec(event->globalPos());
}

void Canvas::on_actionDelete_triggered() {
  emit removeObject();
}

void Canvas::on_actionCut_triggered() {
}

void Canvas::on_actionPaste_triggered() {
}

void Canvas::on_actionProperties_triggered() {
  // Call up the properties for the node.
  emit showPropertiesDialog();
}

void Canvas::on_actionCopy_triggered() {
}
